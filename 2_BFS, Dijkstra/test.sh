#!/bin/bash

NUM=2
EXPECTED="bfs.1.cc bfs.2.cc bfs.3.cc vgraph.h vgraph.cc dijkstra.cc"
FILE="td${NUM}.tar"

function die {
  echo "ERROR: $@"
  exit 1
}

[[ "$#" = 1 ]] || die "Usage: $0 mon_archive.tar"
[[ "${1##*/}" = "$FILE" ]] || die "The archive must be called '$FILE'"

files=$(tar tf "$1") || die "$1 is not a valid tar archive?"

echo "$files" | egrep "^rendu.txt\$" > /dev/null || die "'rendu.txt' not found!!!"
tar xf "$1" rendu.txt
egrep "NumeroEtudiant: ?[1-9][0-9]{7}($|[^0-9])" rendu.txt || die "'NumeroEtudiant' not found or invalid"

for i in $EXPECTED; do
  echo "$files" | egrep "^$i\$" > /dev/null && echo "Found $i" || echo "NOT FOUND: $i"
done
echo "--------"
