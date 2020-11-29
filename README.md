# DecodeAudio

* Folder structured:
    Name | Description
    -- | --
    DecodeAudio | [ Root Directory]
    | \|____DecodeAudio |[ Contains Command Line Interface and Library ]
    | \|____DecodeaudioCLI |[ Command Line Interface ]
    | \|____DecodeAudioLib|[ DecodeAudio library ]
    | \|____ProblemStatement  | [ Audio files and corresponding decoded message and bit stream message for testing. ]
    | \|____test        |   [ Contains all the tests written for the library. ]
    | \|____ThirdParty   | [ Contains all the third party libraries used. ]
    | \|____dr_libs     |  [ Third party library used for reading wave files. ]
    | \|____googletest      |[ Google test library for writing the test case. ]

* Third-party framework used:
    Tool | Purpose | Link
    -- | -- | --
    Google Test | For Testing | <https://github.com/google/googletest>
    Dr_libs | For reading from wav files. | <https://github.com/mackron/dr_libs>


* Steps for building and running:
  * Install cmake

    ```sh
    apt-get install cmake
    ```

  * Creating the build directory

    ```sh
    mkdir build
    cd build
    ```

  * Building the project.

    ```sh
    cmake .. -G "Unix Makefiles"
    cmake --build .
    ```

  * Running the Command line interface. CLI accepts three arguments
    Argement | Description
    --------- | ----------
    --audio "Audio file" | Audio file to decode
    --channel positive_number          |Audio channel to decode in audio file.
    --threshold positive_number       |Sample correction to find the encoded message. Ideally this should be 0 but in distorted audio file it can be about 3 - 10 depending on the distortion.

    ```sh
    cd DecodeAudio/DecodeAudioCLI/
    ./DecodeAudio --audio file_1.wav
    ```

    or

    ```sh
    cd DecodeAudio/DecodeAudioCLI/
    ./DecodeAudio --audio file_1.wav --channel 0
    ```

    or

    ```sh
    cd DecodeAudio/DecodeAudioCLI/
    $ ./DecodeAudio --audio file_1.wav --channel 0 --threshold 4
    ```

  * Running the google test (inside the build folder)

    ```sh
    ctest
    ```

  * Running the specific google test (inside the build folder)

    ```sh
    cd test/DecodeAudioLibTests
    ./DecodeAudioLibTests
    ```
