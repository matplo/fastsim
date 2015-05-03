
#root -l -q "gener.C(50000,20,0,1)" > 50000-20-0-1.log &
#root -l -q "gener.C(50000,25,0,1)" > 50000-25-0-1.log &
#root -l -q "gener.C(50000,20,1,1)" > 50000-20-1-1.log &
#root -l -q "gener.C(50000,25,1,1)" > 50000-25-1-1.log &

#root -l -q "gener.C(50000,5,0,1)" > 50000-5-0-1.log &
#root -l -q "gener.C(50000,5,1,1)" > 50000-5-1-1.log &

#root -l -q "gener.C(50000,35,0,0)" > 50000-35-0-0.log &
#root -l -q "gener.C(50000,35,1,0)" > 50000-35-1-0.log &

root -l -q "gener.C(50000,3,0,1)" > 50000-3-0-1.log &
root -l -q "gener.C(50000,3,1,1)" > 50000-3-1-1.log &

root -l -q "gener.C(50000,35,0,1)" > 50000-35-0-1.log &
root -l -q "gener.C(50000,35,1,1)" > 50000-35-1-1.log &
