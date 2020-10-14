
trap "{ echo 'Bye!' ; exit 0; }" SIGINT

for run in {1..50}
do
  ./ga eil51.tsp
  mv --backup=t  ofile ./results/ofile 
done

