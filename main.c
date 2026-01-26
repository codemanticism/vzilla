#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
char help[] =
"Manager for the V language for Linux.\n"
"install: installs the version specified \n"
"switch: makes the version specified the default \n";
char start[] = 
"\\  //\n"
" \\//ILLA\n";
char* url = "wget https://github.com/vlang/v/releases/download/";
char* v_linux = "/v_linux.zip -O ~/Downloads/v_linux.zip";
struct version{
	unsigned int big;
	unsigned int medium;
	unsigned int mini;
};
typedef struct version version;
int str_to_int(char* ptr_to_char){
	unsigned int result = 0;
	for(;((*ptr_to_char) >= '0')&&((*ptr_to_char) <= '9');ptr_to_char--){
		result *= 10;
		result += ((*ptr_to_char) - '0');
	}
	return result;
}
int help_fn(){
	printf(help);
	FILE *file = fopen("vzillash.sh", "w");
	if (file == NULL) {
        	perror("Error opening file");
        	return 1;
    	}
	char* nothing = "";
    	fprintf(file, nothing);
	fclose(file);
}
int install(char* input, bool switch_or_not){
	printf("\n");
	unsigned int i = 0;
	const char* home = getenv("HOME");
	if(home == NULL){
		printf("Unable to get HOME directory");
		return 1;
	}
	printf(start);
	char* ref_to_input = input;
	version versions[] = {
		{.big = 0, .medium = 5, .mini = 0},
		{.big = 0, .medium = 4, .mini = 12},
		{.big = 0, .medium = 3, .mini = 4},
		{.big = 0, .medium = 2, .mini = 4},
		{.big = 0, .medium = 1, .mini = 29}
	};
	for(;(*input) != '.'; input++){
	}
	input--;
	unsigned int big = str_to_int(input);
	input++;
	for(input++;((*input) != '\0')&&((*input) != '.'); input++){
	}
	input--;
	unsigned int medium = str_to_int(input);
	unsigned int mini = 0;
	if((*input) != '\0'){ // 3 numbers
		input++;
		char* ptr_to_char = input;
		for(input++;(*input) != '\0'; input++){
		}
		input--;
		mini = str_to_int(input);
		if(mini == 0){
			(*ptr_to_char) = '\0';
		}
	}else{ // 2 numbers
		
	}
	bool valid = false;
	for(i = 0; i < (sizeof(versions) / sizeof(version));i++){
		version version_var = versions[i];
		if((version_var.big == big) && (version_var.medium == medium) && (version_var.mini >= mini)){
			valid = true;
			break;
		}
	}
	if(valid == false){
		printf("Invalid version\n");
		exit(1);
	}
	char new_url[(sizeof(url) - 1) + 8 + (sizeof(v_linux) - 1)];
	i = 0;
	for(;(*url) != '\0';i++){
		new_url[i] = *url;
		url++;
	}
	char* copy = ref_to_input;
	for(;(*copy) != '\0';i++){
		new_url[i] = *copy;
		copy++;
	}
	for(;(*v_linux) != '\0';i++){
		new_url[i] = *v_linux;
		v_linux++;
	}
	new_url[i] = '\0';
	i = 0;
	char path[4096];
	char* _ = "#!/bin/sh\nexport PATH=";
	char* another_copy = "/Downloads/v_linux/v";
	if(switch_or_not == false){
		system("rm -rf ~/Downloads/v_linux.zip");
		system("rm -rf ~/Downloads/v_linux");
		system(new_url);
	}
	if(switch_or_not == false){
		system("unzip ~/Downloads/v_linux.zip -d ~/Downloads/v_linux");
	}
	unsigned int before = 0;
    	char* local_bin = "/.local/bin/vlang";
	char* old_path = getenv("PATH");
	char new_old_path[4096];
	i = 0;
	unsigned int start_i = 0;
	unsigned int k = 0;
	bool skip = false;
	for(;1; i++){
		if((old_path[i] != '\0')){
			for(unsigned int j = 0;old_path[i] == local_bin[j];i++){
				j++;
				if(local_bin[j] == '\0'){
					skip = true;
					i--;
					break;
				}
			}
		}
		if( (old_path[i] == ':') || (old_path[i] == '\0')){
			if(skip == false){
				unsigned int j = before;
				for(;(old_path[j] != '\0')&&(old_path[j] != ':');j++){
					new_old_path[k] = old_path[j];
					k++;
				}
				new_old_path[k] = ':';
				k++;
			}
			before = i + 1;
			skip = false;
		}
		if( (old_path[i] == '\0') ){
			break;
		}
	}
	if( new_old_path[k - 1] == ':'){
		new_old_path[k - 1] = '\0';
		new_old_path[k] = '\"';
	}else{
		new_old_path[k] = '\0';
	}
	i = 0;
	
    	if (old_path == NULL) {
        	old_path = ""; 
    	}
	char start_char[] = "cd ~/Downloads/v_linux;mv v ~/.local/bin/vlang";
	char* start = start_char;
	char new_mem[sizeof(start_char) + 8];
	for(i = 0;(*start) != '\0';start++){
		new_mem[i] = *start;
		i++;
	}
	char* another_ref = ref_to_input;
	for(;(*ref_to_input) != '\0';ref_to_input++){
		if((*ref_to_input) != '.'){
			new_mem[i] = *ref_to_input;
		}else{
			new_mem[i] = '-';
		}
		i++;
	}
	new_mem[i] = '\0';
	char new_str_str[] = "rm -rf ~/.local/bin/vlang"; 
	char* new_str = new_str_str;
	char new_mem_2[sizeof(new_str_str) + 8];
	for(i = 0;(*new_str) != '\0';new_str++){
		new_mem_2[i] = *new_str;
		i++;
	}
	char* another_another_ref = another_ref;
	for(;(*another_ref) != '\0';another_ref++){
		if((*another_ref) != '.'){
			new_mem_2[i] = *another_ref;
		}else{
			new_mem_2[i] = '-';
		}
		i++;
	}
	new_mem_2[i] = '\0';
	char command[4096];
	char* export_path = "/.local/bin/vlang";
	i = 0;
	for(;home[i] != '\0';i++){
		command[i] = home[i];
	}
	for(;(*export_path) != '\0';export_path++){
		command[i] = *export_path;
		i++;
	}
	for(;(*another_another_ref) != '\0';another_another_ref++){
		if((*another_another_ref) != '.'){
			command[i] = *another_another_ref;
		}else{
			command[i] = '-';
		}
		i++;
	}
	command[i] = '\0';
	if(switch_or_not == false){
		system(new_mem_2);
		system(new_mem);
	}
	i = 0;
	for(;(*_) != '\0';_++){
		path[i] = *_;
		i++;
	}
	for(unsigned int j = 0;new_old_path[j] != '\0';j++){
		path[i] = new_old_path[j];
		i++;
	}
	path[i] = ':';
	i++;
	for(unsigned int j = 0;command[j];j++){
		path[i] = command[j];
		i++;
	}
	path[i] = '\0';
	FILE *file = fopen("vzillash.sh", "w");
	if (file == NULL) {
        	perror("Error opening file");
        	return 1;
    	}
    	fprintf(file, path);
	fclose(file);
}
int main (int argc, char **argvk){
	if(argc != 3){
		help_fn();
		return 0;
	}
	char* install_keyword = "install";
	char* switch_keyword = "switch";
	bool correct = true;
	unsigned int counter = 0;
	for(;(*install_keyword) != '\0';install_keyword++){
		if(argvk[1][counter] != (*install_keyword)){
			correct = false;
			break;
		}
		counter++;
	}
	if(correct){
		install(argvk[2], false);	
		return 0;
	}
	counter = 0;
	correct = true;
	for(;(*switch_keyword) != '\0';switch_keyword++){
		if(argvk[1][counter] != (*switch_keyword)){
			correct = false;
			break;
		}
		counter++;
	}
	if(correct){
		install(argvk[2], true);
		return 0;
	}
	help_fn(); 

}
