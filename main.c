#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
char help[] =
"Manager for the V language for Linux.\n"
"install: installs the version specified. If already installed, it removes the previous installation.\n"
"switch: makes the version specified the default for the terminal session.\n"
"add: installs the version specified without changing the default.\n"
"delete: deletes the version specified.\n"
"unlist: removes mentions to the V transpiler path from the session's PATH environment variable.\n";
char start[] = 
"\\  //\n"
" \\//ZILLA\n";
char url_char[] = "wget --no-check-certificate https://www.github.com/vlang/v/releases/download/";
char* url = url_char;
char v_linux_char[] = "/v_linux.zip -O ~/.v_downloads/v_linux.zip";
char* v_linux = v_linux_char;
char* nothing = "";
char* job_done = "Job done!\n";
struct version{
	unsigned int major;
	unsigned int minor;
	unsigned int patch;
};
enum command_type{
	SWITCH = 0,
	INSTALL = 1,
	ADD = 2,
	DELETE = 3,
	UNLIST = 4
};
typedef struct version version;
int str_to_int(char* ptr_to_char /*pointer to last digit*/){ 
	unsigned int result = 0;
	for(;((*ptr_to_char) >= '0')&&((*ptr_to_char) <= '9');ptr_to_char--){
		result *= 10;
		result += ((*ptr_to_char) - '0');
	}
	return result;
}
void wait_s(int seconds) {
	sleep(seconds);
}
int help_fn(){
	printf(help);
	FILE *file = fopen("vzillash.sh", "w");
	if (file == NULL) {
        	perror("Error opening file");
        	return 1;
    	}
    	fprintf(file, nothing);
	fclose(file);
}
int runs_command(char* input, enum command_type cmd){
	printf("\n");
	unsigned int i = 0;
	bool going_to_install_something = (cmd == INSTALL) || (cmd == ADD);
	printf(start);
	char* ref_to_input = input;
	version versions[] = {
		{.major = 0, .minor = 5, .patch = 0},
		{.major = 0, .minor = 4, .patch = 12},
		{.major = 0, .minor = 3, .patch = 4},
		{.major = 0, .minor = 2, .patch = 4},
		{.major = 0, .minor = 1, .patch = 29}
	};

	unsigned int major = 0;
	unsigned int minor = 0;
	unsigned int patch = 0;
	if((*input) != '\0'){
		for(;(*input) != '.'; input++){
		}
		input--;
		major = str_to_int(input);
		input++;
		for(input++;((*input) != '\0')&&((*input) != '.'); input++){
		}
		input--;
		minor = str_to_int(input);
		patch = 0;
		if((*input) != '\0'){ // 3 numbers
			input++;
			char* ptr_to_char = input;
			for(input++;(*input) != '\0'; input++){
			}
			input--;
			patch = str_to_int(input);
			if(patch == 0){
				(*ptr_to_char) = '\0';
			}
		}	
		bool valid = false;
		for(i = 0; i < (sizeof(versions) / sizeof(version));i++){
			version version_var = versions[i];
			if((version_var.major == major) && (version_var.minor == minor) && (version_var.patch >= patch)){
				valid = true;
				break;
			}
		}
		if(valid == false){
			printf("Invalid version\n");
			exit(1);
		}
	}

	char new_url[(sizeof(url_char) - 1) + 9 + (sizeof(v_linux_char) - 1)];
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
	system("mkdir ~/.v_downloads");
	if(going_to_install_something){
		system("rm -rf ~/.v_downloads/v_linux.zip");
		system("rm -rf ~/.v_downloads/v_linux");
		printf("\n");
		printf(new_url);
		printf("\n");
		system(new_url);
	}
	if(going_to_install_something){
		system("unzip ~/.v_downloads/v_linux.zip -d ~/.v_downloads/v_linux");
	}
	unsigned int before = 0;

    	char* local_bin = "/usr/bin/vlang"; //to remove references to that from the environment key.
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
	char start_of_command[] = "#!/bin/sh\nexport PATH=";
	char new_command[(sizeof(start_of_command) - 1) + 4096];
	for(;start_of_command[i] != '\0';i++){
		new_command[i] = start_of_command[i];
	}
	for(unsigned int j = 0; new_old_path[j] != '\0';j++){
		new_command[i] = new_old_path[j];
		i++;
	}
	new_command[i] = '\0';

	if(cmd == UNLIST){
		FILE *file = fopen("vzillash.sh", "w");
		fprintf(file, new_command);
		fclose(file);
		printf(job_done);
		return 0;
	}
    	if (old_path == NULL) {
        	old_path = ""; 
    	}

	char start_char[] = "cd ~/.v_downloads/v_linux;sudo mv v /usr/bin/vlang";
	char* start = start_char;
	char move_command[(sizeof(start_char) - 1) + 8];
	for(i = 0;(*start) != '\0';start++){
		move_command[i] = *start;
		i++;
	}
	char* another_ref = ref_to_input;
	for(;(*ref_to_input) != '\0';ref_to_input++){
		if((*ref_to_input) != '.'){
			move_command[i] = *ref_to_input;
		}else{
			move_command[i] = '-';
		}
		i++;
	}
	move_command[i] = '\0';

	char new_str_str[] = "sudo rm -rf /usr/bin/vlang"; 
	char* new_str = new_str_str;
	char rm_command[(sizeof(new_str_str) - 1) + 8];
	for(i = 0;(*new_str) != '\0';new_str++){
		rm_command[i] = *new_str;
		i++;
	}
	char* another_another_ref = another_ref;
	for(;(*another_ref) != '\0';another_ref++){
		if((*another_ref) != '.'){
			rm_command[i] = *another_ref;
		}else{
			rm_command[i] = '-';
		}
		i++;
	}
	rm_command[i] = '\0';

	char command[4096];
	char* export_path = "/usr/bin/vlang";
	i = 0;
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

	if((going_to_install_something)||(cmd == DELETE)){ //deletes previous installation from system
		printf("If there's any previous installation of this exact version, the following command is supposed to clear it up.\n");
		printf(rm_command);
		printf("\n");
		for(unsigned int sec_to_wait = 10;1;sec_to_wait--){
			printf("Do you want to execute this operation? (seconds: %u)\n", sec_to_wait);
			wait_s(1);
			if(sec_to_wait == 0){
				break;
			}
		}
		char str[100];
		printf(rm_command);
		while(1){
			printf("\nType in `yes` precisely, else press CTRL+C to quit the program: \n");
			fgets(str, sizeof(str), stdin);
			if( (str[0] == 'y') && (str[1] == 'e') && (str[2] == 's') ){
				break;	
			}
		}
		
		system(rm_command);
	}
	if(going_to_install_something){
		system(move_command);
	}

	i = 0;
	char* start_of_command_ptr = &(start_of_command[0]);
	for(;(*start_of_command_ptr) != '\0';start_of_command_ptr++){
		path[i] = *start_of_command_ptr;
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
	if((cmd == INSTALL)||(cmd == SWITCH)){ //switches the current
		if (file == NULL) {
        		perror("Error opening file");
        		return 1;
    		}
	}else{
		if (file == NULL) {
        		perror("Error opening file");
        		return 1;
    		}
		path[0] = '\0';
	}

    	fprintf(file, path);
	fclose(file);
	printf(job_done);
}
int main (int argc, char **argvk){
	char* keywords = "switch\0install\0add\0delete\0unlist\0";
	enum command_type a_command = 0;
	if(argc <= 1){
		help_fn();
		return 0;
	}
	do{
		bool correct = true;
		unsigned int counter = 0;
		for(;(*keywords) != '\0';keywords++){
			if(argvk[1][counter] != (*keywords)){
				correct = false;
				for(;(*keywords) != '\0'; keywords++){

				}
				break;
			}
			counter++;
		}
		if(correct){
			if(a_command != UNLIST){
				if(argc != 3){
					help_fn();
					return 0;
				}
				runs_command(argvk[2], a_command);
				return 0;
			}
			runs_command(nothing, a_command);	
			return 0;
		}
		a_command++;
		keywords++;
	} while ((*keywords) != '\0');
	help_fn(); 
}
