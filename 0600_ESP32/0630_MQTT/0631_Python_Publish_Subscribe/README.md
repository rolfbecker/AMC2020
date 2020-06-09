
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

## Install MQTT Command Line Clients (requires root priviledges, aka sudo)
```
sudo apt update
sudo apt search mqtt
sudo apt install mosquitto-clients
```

## Install the Paho MQTT Module for Python

Login as studi and open a terminal. Execute:
```
conda install -c conda-forge paho-mqtt
```

Open `Jupyter-Lab` (e.g. via `Anaconda Navigator`) and change to the directory of the MQTT Python notebooks `publisher_V003.ipynb` and `subscriber_V003.ipynb`, e.g.
```
/home/studi/Arduino/AMC2020/0600_ESP32/0630_MQTT/0631_Python_Publish_Subscribe
```
Open the notebooks in Jupyter. Read the code and understand.

1. Execute the **subscriber first**. It is an infinite loop. The code does not stop on its own. You have to stop the execution of the cell or interrupt the kernel.
1. Execute the **publisher second**. The cell executions publish a simple text message. Look at the subscriber. It should have received it.

Many publishers and subscribers can use the same topic.




