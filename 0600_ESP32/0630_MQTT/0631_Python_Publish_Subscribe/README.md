
# Installation of MQTT Related Software Packages under Linux VM

## Change to new remote repo location

We changed the central repo from `https://gitlab.spectors.eu/rolf/AMC2020` to `https://github.com/rolfbecker/AMC2020`.


Login as studi and open a terminal. 

Change local directory to   
```
cd /home/studi/Arduino/
```

With `ls`you should see the old AMC2020 repo. Move it away:
```
mv AMC2020 AMC2020_old_gitlab
```

Clone the new repo from `github.com`:
```
git clone https://github.com/rolfbecker/AMC2020.git
```

In case you have cloned from `github.com` already pull the repo (update local from remote):
```
cd AMC2020
git pull
```


## Install the Paho MQTT Module for Python

Login as studi and open a terminal. Execute:
```
conda install -c conda-forge paho-mqtt
```




Change to super user (root priviledges, admin, sudo):

```
sudo -i
```



