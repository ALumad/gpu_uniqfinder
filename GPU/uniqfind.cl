__kernel void uniqfind(__global int *in_vec,  __global int *out_vec) 
{
   const int n = get_global_id(0);
   out_vec[in_vec[n]-1] = in_vec[n]; //All threads set the same value, so it should be safe. 

}

