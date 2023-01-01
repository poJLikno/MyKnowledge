//for string
string str = to_string(num);
int num_1 = stoi(str);

//for C string
char c_str[20] = {};
snprintf(c_str, 20, "%d", num_2);
int num_2 = atoi(c_str);
