//We need 3 parts to this, motor control, sensor control, and json packaging
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include <httplib.h>
#include <json/single_include/nlohmann/json.hpp>
using namespace std; //hopefully this namespace does not mess stuff up lol
using json = nlohmann::json;
#define ll double
vector<pair<ll, ll> > time_depth;
ll beginning_pressure = LLONG_MIN;
ll motor_counter = 0; //beginning bouyancy
ll unit_kPa = 1013.25; //this might be a different conversion unit
ll unit_Pa = 101325;
ll height = 2.5;
//TODO: Implement a PID algorithm for this
//TODO: Finish Dive
//TODO: Finish Read
//TODO: Setpower


void post_request(){
    //Create our client to send POST Request
    httplib::Client cli("http://127.0.0.1:5000/data");
    json data; //Creates a json object with character data
    for(auto i: time_depth){
        ll time = i.first;
        ll depth = i.second;
        array<ll, 2> arr = {time, depth};
        data["(t,d)"].emplace_back(arr);
    }
    // (Path request will be sent <-data endpoint, data.dump() just dumps the data from json object into string, content-type header <- tells the server what to expect)
    auto res = cli.Post("/data", data.dump(), "application/json")
    if (res && res->status == 200) {
        cout << "Successfully posted data." << endl;
    } else {
        cout << "Failed to post data." << endl;
    }
    return;
}
ll read(){

}
void setPower(ll power){

}

ll convert_pressure_to_distance(ll pressure){
    /*
    p = pgh
    where,
    p is the pressure exerted by the liquid in N.m-2 or Pa
    ρ is the density of the liquid in kg.m-3, slugs.ft-3
    g is the acceleration due to gravity taken as 9.81m.s-2
    h is the height of the fluid column in m
    */
   ll convert_p = pressure/unit_kPa * unit_Pa;
   ll h = convert_p/(9.81*997);
   return h;
}
void dive(int beginning_pressure){
    ll cur_pressure = read();
    while(cur_pressure >= beginning_pressure){
        setPower(MXPOWER);
        this_thread::sleep_for(chrono::seconds(1));  // Sleep for 1 second
        cur_pressure = read();
    }
    while(cur_pressure<=beginning_pressure){
        if(convert_pressure_to_distance(cur_pressure)>height-0.5)
    }
    post_request();

}
int main(){
    //layout for main 
    if(beginning_pressure == LLONG_MIN){
        beginning_pressure = read();
    }
    dive();
    beginning_pressure = read();
    dive();

}