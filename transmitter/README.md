# Transmitter side
This is a tool used to write layer weights to a Thingy:53.

Not suited for generic usage but might serve as inspiration for someone else.

## How to build
```sh
mkdir build
cd build
cmake ..
cmake --build .
```

### NOTE: this assumes weights are placed in a header called weights.h
An example of how to describe the layers is in `map.toml` 
