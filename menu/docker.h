#ifndef DOCKER_H
#define DOCKER_H

#include "base.h"

MenuItem* Method::get_docker_ptr(){
    MenuItem* docker_ptr = new MenuItem;
    docker_ptr->name = "docker";
    docker_ptr->submenu = {
        {"docker +", {
            {"login +", {{"*login user/pwd to dockerhub#docker login#dockerlogin"},
                         {"*login user/pwd to specific registry#docker login ${self-hosted registry}#dockerlogin"}}},
            {"settings +", {{"display system-wide info#docker info#"},
                            {"*show all existed user configs for dockerd#cat /etc/docker/daemon.json#dockerd"}}},
            {"image +", {{"show all images#docker images#"},
                         {"pull docker image by certain digest & tag#docker image pull ${image}:${tag}@${digest}#"},
                         {"*build img using default dockerfile in current dir#docker build -t ${image}:${tag} .#dockerbuild"},
                         {"*build img using specified dockerkfile#docker build -f ${dockerfile_name} -t ${image}:${tag} .#dockerbuild"},
                         {"*build img in multi-stage way#see desc/dockerfile for details#docker multistage build"},
                         {"check detailed img info (rootfs, exposed port...)#docker image inspect ${image}#"},
                         {"export docker image to local tar file#docker save -o ${output}.tar ${image}:latest#"},
                         {"import local tar file into docker image#docker load -i ${input.tar}#"}}},
            {"history +", {{"show image build history(cmd/arg/env)#docker history ${image} -H#"},
                           {"show image build history in verbose(cmd/arg/env)#docker history ${image} --no-trunc#"}}},
            {"manifest +", {{"check whether img:tag already existed in remote, 0:existed, 1:none#docker manifest inspect ${img}:${tag} > /dev/null; echo $?#"}}},
            {"container +", {{"show containers dead or alive (detailed)#docker ps -a#"},
                             {"show containers dead or alive (only id)#docker ps -a -q#"},
                             {"show containers belong to certain image#docker ps -a --filter ancestor=${image:tag}#"},
                             {"show static info of container#docker inspect ${id_or_name}#"},
                             {"show pid of container#docker inspect -f '{{.State.Pid}}' ${id_or_name}#"},
                             {"show ip of container#docker inspect -f '{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}' ${id_or_name}#"},
                             {"show port mapping info of container#docker container port ${id or name}#"},
                             {"show all inspectable info about a container#docker container inspect -f '{{json .}}' cranky_maxwell | jq#"},
                             {"show resource stat info of a container#docker container stats --no-trunc ${id/name}#"},
                             {"show the filesystem diff between container & its image (A: add, C: change)#docker container diff ${containerid}#"},
                             {"show size/virtual of container (size: disk for each container, virtual: disk for readonly img of each container)#docker ps --size ${container}#"},
                             {"attach to an existed running container#docker attach ${id_or_name}#"},
                             {"remove all stopped container#docker container prune#"}}},
            {"run +", {{"start container with env var +", {{"*set env var from cmdline#docker run -e ${key}=${value} ${image}#dockerenvvar"},
                                                           {"*set env var from file#docker run --env-file ${file} ${image}#dockerenvvar"}}},
                       {"start container and remove it when exit#docker run --rm ${image}#"},
                       {"start container and login as an existed user#docker run -it --rm --user ${username} ${image} bash#"},
                       {"*start container with perf tool PMU event collection enabled#docker run -it --security-opt seccomp=${perfenable.json} --rm ${image} bash#dockerperf"}}},
            {"network +", {{"show docker network manager help info#docker network --help#"},
                           {"show available network driver info#docker network ls#"},
                           {"create a network in docker#docker network create ${networkname}#"},
                           {"remove 1/more networks in docker#docker network rm ${networknames}#"},
                           {"remove all unused networks in docker with prompt#docker network prune#"},
                           {"show detailed info for a network driver by name/id#docker network inspect ${network name/id}#"},
                           {"start container sharing the network of host#docker run -it --rm --privileged=true --network=host ${image} sh#"},
                           {"start container sharing the network of certain container#docker run -it --rm --privileged=true --network=container:${containerid} ${image} sh#"}}},
            {"port +", {{"list port mapping info of a container#docker port ${containerid}#"}}},
            {"log +", {{"show docker daemon log in syslog (tail -f /var/log/messages or /var/log/syslog)#see docker doc: read the daemon logs#"}}},
            {"system +", {{"show manual#docker system --help#"},
                          {"show docker system disk consumption#docker system df#"},
                          {"show docker system disk consumption in details#docker system df -v#"},
                          {"show docker system level info#docker system info#"}}},
            {"stats +", {{"show manual#docker stats --help#"},
                         {"show CPU%, MEM-USAGE/LIMIT, MEM%, NET-I/O, BLOCK-I/O, PIDS of a container#docker stats ${container}#"},
                         {"show CPU%, MEM-USAGE/LIMIT, MEM%, NET-I/O, BLOCK-I/O, PIDS of all container#docker stats --all#"}}},
            {"volume +", {{"show docker container volume info formatted by jq#docker container inspect -f '{{json .Config.Volumes}}' ${container_name/id} | jq#"}}},
            {"mount +", {{"show docker container mount info formatted by jq#docker container inspect -f '{{json .Mounts}}' ${container_name/id} | jq#"}}},
            {"cache +", {{"remove all unused docker build cache#docker builder prune --all#"}}},
            {"file/dirs +", {{"copy file/dir from container to host#docker cp ${container_id}:${absolute_path} ${hostdir}#"},
                             {"copy file/dir from host to container#docker cp ${hostdir} ${container_id}:${absolute_path}#"}}}}},
    };
    return docker_ptr;
}

#endif
