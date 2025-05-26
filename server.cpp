#include "httplib.h"
#include "json/single_include/nlohmann/json.hpp"
#include <stack>
#include <iostream>
using json = nlohmann::json;
std::stack<json> json_stack;

//https://developer.mozilla.org/en-US/docs/Web/HTTP/MIME_types/Common_types
//content_type in our requests is MIME type

int main() {
    using namespace httplib;
    Server svr;

    svr.Get("/", [](const Request& req, Response& res) {
        std::string html = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Stack Size</title>
    <script>
        function updateStackSize() {
            fetch('/ss')
                .then(response => {
                    if (!response.ok) {
                        throw new Error('Network response was not ok');
                    }
                    return response.text();
                })
                .then(data => {
                    document.getElementById('ss').innerText = data;
                })
                .catch(error => {
                    console.error('Error fetching stack size:', error);
                });
        }

        // Poll the server every 2 seconds
        setInterval(updateStackSize, 2000);

        // Initial update
        updateStackSize();
    </script>
</head>
<body>
    <h1>Current Stack Size: <span id="ss">Loading...</span></h1>
</body>
</html>
)";
        res.set_content(html, "text/html");
    });
    
    //instead use js to js poll it randomly
    //get stacksize (httplib is single threaded, don't block '/' making the server unresponsive)
    svr.Get("/ss", [](const Request& req, Response& res) {
        std::string size = std::to_string(json_stack.size());
        res.set_content(size, "text/plain");
    });

    //Get data from server
    svr.Get("/plot", [](const Request& req, Response& res){
        if(!json_stack.empty()){
            nlohmann::json cur = json_stack.top();
            json_stack.pop();
            res.set_content(cur.dump(), "application/json");
            //https://json.nlohmann.me/api/basic_json/dump/
            //make sure that our json objects become json strings
            //because our mime type of application/json is only json strings for some reason?
        }else{
            res.status = 204; //No Content Avilable Refer to StatusCodeReference.txt for future references on status codes
        }
    });


    svr.Post("/input", [](const Request& req, Response& res) {
        if (req.has_header("Content-Type") && req.get_header_value("Content-Type") == "application/json"){
            try {
                json body = json::parse(req.body);
                std::cout << "JSON Data: " << body.dump() << std::endl;
                json_stack.push(body);
                res.set_content("OK", "text/plain");
            }catch (const json::parse_error& e) {
                res.status = 400;
                std::cout<<"Invalid Req"<<" "<<std::string(e.what())<<std::endl;
                res.set_content("Invalid JSON: " + std::string(e.what()), "text/plain");
            }
        }else{
            //BadRequest_400 = 400,
            res.status = 400;
            res.set_content("Bad Content Type (not json)", "text/plain");
        }   
    });

    // Start the server. Port 5000
    svr.listen("0.0.0.0", 5000);
}

//compile the file with:
//currently compiling with 
//linking with this ee
//g++ server.cpp -o server.exe -static -lws2_32 -lpthread
//lws is winsock is a network assignment for windows?
//compile on mac with g++ -std=c++17 server.cpp
