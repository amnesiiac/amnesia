#ifndef HTTP_H
#define HTTP_H

#include "base.h"

MenuItem* Method::get_http_ptr(){
    MenuItem* http_ptr = new MenuItem;
    http_ptr->name = "http";
    http_ptr->submenu = {
        {"http +", {{"curl +", {{"use http GET method to derive info#curl ${ip}:${port}/${route} -v#"},
                                {"use http POST method to publish json data to route#curl ${ip}:${port}/${route} --include --header 'Content-Type: application/json' --request 'POST' --data '${serialized_json}'#"}}},
                    {"wget +"}}},
    };
    return http_ptr;
}

#endif
