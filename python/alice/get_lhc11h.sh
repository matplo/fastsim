 #!/bin/bash

#alien_find /alice/data/2011/LHC11h_2/000170207/ESDs/pass2 root_archive.zip | tee file_list.
rnumber=000170207
#alien_find /alice/data/2011/LHC11h/$rnumber/raw raw.roow | tee file_list_$rnumber.raw
#alien_ls /alice/data/2011/LHC11h/$rnumber/raw | grep .root | tee "file_list_$rnumber_raw.txt"

#./get_raw.py -n 10 -r 000170207
#./get_raw.py -n 100 -r 170388
./get_raw.py -r 170388
./get_raw.py --all -r 170388 --no-sort

# this is for LHC15o
#./get_raw.py -n 10 -r 000246751

