﻿# PacketFile
void dynamicArray(int n)
{
	float *x;
	try{
		x=new float[n];
	}
	catch(bad_alloc e)
	{
		cerr<<"Out of memory"<<endl;
		exit(1);
	}
    for(int i=0; i<n; i++)
	{
		 x[i]=i+0.1;
	}
	for(int i=0;i<n;i++)
		cout<<x[i]<<endl;
	delete []x;
}
