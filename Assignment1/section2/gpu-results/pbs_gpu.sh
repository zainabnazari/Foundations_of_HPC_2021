#!/bin/bash

#PBS -l nodes=2:ppn=24
#PBS -l walltime=01:00:00
#PBS -q dssc_gpu

cd "$PBS_O_WORKDIR"

module load openmpi-4.1.1+gnu-9.3.0 2>/dev/null

mpirun -np 2 --report-bindings --map-by core --mca pml ob1 --mca btl self,tcp --mca btl_tcp_if_include br0 ./IMB-MPI1 PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | sed -r 's/  */,/g' | cut -d "," -f2- >result_core_ob1_tcp_br0.csv
mpirun -np 2 --report-bindings --map-by core --mca pml ob1 --mca btl self,tcp --mca btl_tcp_if_include ib0 ./IMB-MPI1 PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | sed -r 's/  */,/g' | cut -d "," -f2- >result_core_ob1_tcp_ib0.csv

mpirun -np 2 --report-bindings --map-by core --mca pml ob1 --mca btl self,vader  ./IMB-MPI1 PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | sed -r 's/  */,/g' | cut -d "," -f2- >result_core_ob1_vader.csv


mpirun -np 2 --report-bindings --map-by core --mca pml ucx ./IMB-MPI1 PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | sed -r 's/  */,/g' | cut -d "," -f2- >result_core_ucx.csv


mpirun -np 2 --report-bindings --map-by socket --mca pml ob1 --mca btl self,tcp --mca btl_tcp_if_include br0 ./IMB-MPI1 PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | sed -r 's/  */,/g' | cut -d "," -f2- >result_socket_ob1_tcp_br0.csv
mpirun -np 2 --report-bindings --map-by socket --mca pml ob1 --mca btl self,tcp --mca btl_tcp_if_include ib0 ./IMB-MPI1 PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | sed -r 's/  */,/g' | cut -d "," -f2- >result_socket_ob1_tcp_ib0.csv

mpirun -np 2 --report-bindings --map-by socket --mca pml ob1 --mca btl self,vader  ./IMB-MPI1 PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | sed -r 's/  */,/g' | cut -d "," -f2- >result_socket_ob1_vader.csv

mpirun -np 2 --report-bindings --map-by socket --mca pml ucx ./IMB-MPI1 PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | sed -r 's/  */,/g' | cut -d "," -f2- >result_socket_ucx.csv



mpirun -np 2 --report-bindings --map-by node --mca pml ob1 --mca btl self,tcp --mca btl_tcp_if_include br0 ./IMB-MPI1 PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | sed -r 's/  */,/g' | cut -d "," -f2- >result_node_ob1_tcp_br0.csv


mpirun -np 2 --report-bindings --map-by node --mca pml ob1 --mca btl self,tcp --mca btl_tcp_if_include ib0 ./IMB-MPI1 PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | sed -r 's/  */,/g' | cut -d "," -f2- >result_node_ob1_tcp_ib0.csv


mpirun -np 2 --report-bindings --map-by node --mca pml ucx --mca btl self,tcp --mca btl_tcp_if_include ib0 ./IMB-MPI1 PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | sed -r 's/  */,/g' | cut -d "," -f2- >result_node_ucx_tcp_ib0.csv


module purge 2>/dev/null
module load intel 2>/dev/null

mpiexec -np 2 -env I_MPI_DEBUG 5 -genv I_MPI_FABRICS=shm -genv  I_MPI_PIN_PROCESSOR_LIST 0,1  ./IMB-MPI1_intel PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | grep -v '^\[' | sed -r 's/  */,/g' | cut -d "," -f2- >result_core_shm_intel.csv


mpiexec -np 2 -env I_MPI_DEBUG 5 -genv I_MPI_FABRICS=shm -genv  I_MPI_PIN_PROCESSOR_LIST 0,2  ./IMB-MPI1_intel PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | grep -v '^\[' | sed -r 's/  */,/g' | cut -d "," -f2- >result_socket_shm_intel.csv

mpiexec -np 2 -env I_MPI_DEBUG 5 -genv I_MPI_FABRICS=ofi -genv I_MPI_OFI_PROVIDER=tcp -genv I_MPI_PIN_PROCESSOR_LIST 0,1 ./IMB-MPI1_intel PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | grep -v '^\[' | sed -r 's/  */,/g' | cut -d "," -f2- >result_core_ofi_tcp_intel.csv


mpiexec -np 2 -env I_MPI_DEBUG 5 -genv I_MPI_FABRICS=ofi -genv I_MPI_OFI_PROVIDER=tcp -genv I_MPI_PIN_PROCESSOR_LIST 0,2 ./IMB-MPI1_intel PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | grep -v '^\[' | sed -r 's/  */,/g' | cut -d "," -f2- >result_socket_ofi_tcp_intel.csv


mpiexec -np 2 -env I_MPI_DEBUG 5 -genv I_MPI_FABRICS=ofi -genv I_MPI_OFI_PROVIDER=mlx -genv I_MPI_PIN_PROCESSOR_LIST 0,2 ./IMB-MPI1_intel PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | grep -v '^\[' | sed -r 's/  */,/g' | cut -d "," -f2- >result_socket_ofi_mlx_intel.csv


mpiexec -np 2 -env I_MPI_DEBUG 5 -genv I_MPI_FABRICS=ofi -genv I_MPI_OFI_PROVIDER=mlx -genv I_MPI_PIN_PROCESSOR_LIST 0,1 ./IMB-MPI1_intel PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | grep -v '^\[' | sed -r 's/  */,/g' | cut -d "," -f2- >result_core_ofi_mlx_intel.csv

mpiexec -np 2 -env I_MPI_DEBUG 5 -genv I_MPI_FABRICS=ofi -genv I_MPI_OFI_PROVIDER=sockets -genv I_MPI_PIN_PROCESSOR_LIST 0,1 ./IMB-MPI1_intel PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | grep -v '^\[' | sed -r 's/  */,/g' | cut -d "," -f2- >result_core_ofi_sockets_intel.csv


mpiexec -np 2 -env I_MPI_DEBUG 5 -genv I_MPI_FABRICS=ofi -genv I_MPI_OFI_PROVIDER=sockets -genv I_MPI_PIN_PROCESSOR_LIST 0,2 ./IMB-MPI1_intel PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | grep -v '^\[' | sed -r 's/  */,/g' | cut -d "," -f2- >result_socket_ofi_sockets_intel.csv

mpiexec -np 2 -ppn=1 -env I_MPI_DEBUG 5 -genv I_MPI_FABRICS=ofi -genv I_MPI_OFI_PROVIDER=tcp ./IMB-MPI1_intel PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | grep -v '^\[' | sed -r 's/  */,/g' | cut -d "," -f2-  | tail -n +3 >result_node_ofi_tcp_intel.csv


mpiexec -np 2 -ppn=1 -env I_MPI_DEBUG 5 -genv I_MPI_FABRICS=ofi -genv I_MPI_OFI_PROVIDER=mlx ./IMB-MPI1_intel PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | grep -v '^\[' | sed -r 's/  */,/g' | cut -d "," -f2-  | tail -n +3 >result_node_ofi_mlx_intel.csv


mpiexec -np 2 -ppn=1 -env I_MPI_DEBUG 5 -genv I_MPI_FABRICS=ofi -genv I_MPI_OFI_PROVIDER=sockets ./IMB-MPI1_intel PingPong -msglog 28 2>/dev/null | grep -v ^\# | grep -v '^$' | grep -v '^\[' | sed -r 's/  */,/g' | cut -d "," -f2- | tail -n +3 >result_node_ofi_sockets_intel.csv


