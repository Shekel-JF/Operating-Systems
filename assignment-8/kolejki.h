struct my_Struct
{
	char result_queue[32];
	int val1;
	int val2;
	char operator;
};

const char* to_bytes(struct my_Struct* struct_object)
{
	return (const char*)struct_object;
}

struct my_Struct* from_bytes(const char* bytes)
{
	return (struct my_Struct*)bytes;
}
