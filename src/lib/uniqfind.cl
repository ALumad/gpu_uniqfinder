
__kernel void uniqfind(__global int *in_vec, __global int *out_vec, __global bool *fullness_check, int out_size) 
{
   const int idx = abs(in_vec[get_global_id(0)]) % out_size;
   const int value = in_vec[get_global_id(0)];
   
   barrier(CLK_LOCAL_MEM_FENCE);
   
   if (!fullness_check[idx]) {
      out_vec[idx] = value;
      fullness_check[idx] = true;
   } else if (out_vec[idx] != value) { 
      //implement Open addressing strategy 
      for (int i=0; i < out_size && out_vec[i] != value; ++i ) {
         if (!fullness_check[i]) {
            out_vec[i] = value;
            fullness_check[i] = true;
            break;
         }
      }
   }
}

