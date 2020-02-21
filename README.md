# DecodeWave

Install cmake
```sh
$ apt-get install cmake
```

Creating the build directory
```sh
$ mkdir build
$ cd build
```
Building the project.
```sh
$ cmake .. -G "Unix Makefiles"
$ cmake --build . 
```
Running the Command line interface
```sh
$ cd DecodeWave/DecodeWaveCLI/
$ ./DecodeWave --audio file_1.wav
```
or
```sh
$ cd DecodeWave/DecodeWaveCLI/
$ ./DecodeWave --audio file_1.wav --channel 0
```

Running the google test (inside the build folder)
```sh
$ ctest
```
Running the specific google test (inside the build folder) 
```sh
$ cd test/DecodeWaveLibTests
$ ./DecodeWaveLibTests
```