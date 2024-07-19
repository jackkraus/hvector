# hvector
from the hvector.c ROOT tutorial

Motivation: To use a toy model to view the differences in modified configurations of Athena and ROOT to investigate the branch compression and memory usage. 
Method: Build ROOT with changes that don't affect the binaries that need to agree with Athena. 

What we found was not a significant gain in compression after pre-configuring the basket size to exceed no more than 128*1024 kilobytes. 


----
When using a modified build of ROOT, run `lsetup` with:

```
lsetup "asetup none, gcc11, cmakesetup --cmakeversion=3.24.3"
```

---

The directories structure: 

- `ROOT_dev/`
  - `build_dir/`
  - `install_dir/`
  - `root_src/`
- `hvector/`
  - `writeROOTFile.c`
  - `readROOTFile.c`  

---

In `build_dir/`
```
cmake -DCMAKE_INSTALL_PREFIX=/ROOT_dev/install_dir /ROOT_dev/root_src
```
and
```
cmake --build . --target install
```

My `ROOT_dev/root_src/` is found: https://github.com/arthurkraus3/root/tree/development

Then you'll change the source of ROOT by doing: 

```
source /ROOT_dev/install_dir/bin/thisroot.sh 
```

--- 
