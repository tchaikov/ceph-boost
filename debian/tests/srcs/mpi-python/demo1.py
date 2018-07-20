# https://www.boost.org/doc/libs/1_67_0/doc/html/mpi/tutorial.html#mpi.python

import boost.mpi as mpi

print "I am process %d of %d." % (mpi.rank, mpi.size)
