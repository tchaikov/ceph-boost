# https://www.boost.org/doc/libs/1_67_0/doc/html/mpi/tutorial.html#mpi.python

import boost.mpi as mpi

if mpi.world.rank == 0:
    mpi.world.send(1, 0, 'Hello')
    msg = mpi.world.recv(1, 1)
    print msg, '!'
else:
    msg = mpi.world.recv(0, 0)
    print (msg + ', '),
    mpi.world.send(0, 1, 'world')
