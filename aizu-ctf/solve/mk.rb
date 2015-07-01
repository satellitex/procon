N=10000
M=10000
K=5
Q=1000000

print N," ",M," ",K," ",Q,"\n"

Q.times{ |i|
  a=rand(N)
  b=rand(100)+M-99
  c=rand(N)
  print a," ",b," ",c,"\n"
}
