# README.md

to run these scripts you're going to need to build the version of athena that has my `xAOD::DummyElectron` object involved, instructions to build that are found [here](https://github.com/jackkraus/readxAOD-script)

Make sure you build and source properly and from there, you'll need to clone this repo:
```
git clone https://github.com/jackkraus/hvector.git
```

and then you'll need to run root and execute the following commands: 
```
$ root -l
root [0] .x writeROOTFile_dummyElectron.c
( ... output here ... )
root [1] .x readROOTFile_dummyElectron.c
( ... more output ... )
```
