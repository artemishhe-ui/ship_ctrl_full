# ship_ctrl_full
assemble multiple prjs to finaly become ship ctrl app

# prepare

install libboost-all
```bash 
sudo apt-get install libboost-all-dev

``` 

install glog

```bash
git clone https://github.com/google/glog.git
cd glog

cmake -S . -B build -G "Unix Makefiles"

cmake --build build

cmake --build build --target test

sudo cmake --build build --target install
```

building main code

```bash

cmake -S . -B build -G "Unix Makefiles"
cmake --build build

cmake --build build --target test
```
you should probably run tests on main