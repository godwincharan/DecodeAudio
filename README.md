# DecodeWave

Install cmake
$apt-get install cmake

Creating the build directory
$mkdir build
$cd build

Building the project.
$cmake .. -G "Unix Makefiles"
$cmake --build . 

Running the Command line interface
$cd DecodeWave/DecodeWaveCLI/
$./DecodeWave --audio file_1.wav
or
$./DecodeWave --audio file_1.wav --channel 0

Running the google test (inside the build folder)
$cd test/DecodeWaveLibTests
$./DecodeWaveLibTests