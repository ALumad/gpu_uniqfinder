__kernel void uniqfind(__global int *in_vec,  __global int *out_vec,  int out_size) 
{
   const int idx = abs(in_vec[get_global_id(0)]) % out_size;
   const int value = in_vec[get_global_id(0)];
   barrier(CLK_LOCAL_MEM_FENCE);
   
   if (out_vec[idx] == 0) {
      out_vec[idx] = value; 
   } else if (out_vec[idx] != value) { 
      //implement Open addressing strategy 
      for (int i=0; i < out_size && out_vec[i] != value; ++i ) {
         if (out_vec[i] == 0) {
            out_vec[i] = value;
            break;
         }
      }
   }
}

