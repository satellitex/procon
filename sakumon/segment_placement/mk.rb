Q = 10
MAX = 10
print Q,"\n"
Q.times{
  x = rand(MAX)
  y1 = rand(MAX)
  y2 = rand(MAX)
  if rand(2) == 0 
    print x," ",y1," ",x," ",y2,"\n"
  else
    print y1," ",x," ",y2," ",x,"\n"
  end
}
