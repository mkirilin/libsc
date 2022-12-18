/*
  This file is part of the SC Library, version 3.
  The SC Library provides support for parallel scientific applications.

  Copyright (C) 2019 individual authors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

#include <sc3_mpienv.h>

int
main (int argc, char **argv)
{
  sc3_MPI_Info_t      info_noncontig;
  int                *nodesizemem;
  sc3_MPI_Win_t       nodesizewin;

  SC3X (sc3_MPI_Init (&argc, &argv));

  SC3X (sc3_MPI_Info_create (&info_noncontig));
  SC3X (sc3_MPI_Info_set
        (info_noncontig, "alloc_shared_noncontig", "false"));

  sc3_MPI_Win_allocate_shared
        (sizeof (int), sizeof (int),
         info_noncontig, SC3_MPI_COMM_WORLD, &nodesizemem, &nodesizewin);

  SC3X (sc3_MPI_Win_free (&nodesizewin));
  SC3X (sc3_MPI_Info_free (&info_noncontig));

  SC3X (sc3_MPI_Finalize ());
  return 0;
}
