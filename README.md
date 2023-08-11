# gemm
Can you multiply a matrix?


This code is from the following George Hotz video:
https://www.youtube.com/watch?v=VgSQ1GOC86s&t=4034s


I will later change the fused multiply-add so that it can run on arm processors. 

_mm256_fmadd_ps  -> vfmaq_f32 

vfmaq_f32 does not need to be type casted. 

