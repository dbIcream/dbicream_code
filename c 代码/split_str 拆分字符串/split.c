
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


struct strtok_str_s {
	char *str;
	char *cur_str;
	char tok;
	int is_first_word;
};
typedef struct strtok_str_s strtok_str_t;

void init_strtok_str(strtok_str_t *strtok_item, const char *str, char tok)
{
	assert(str != NULL);
	strtok_item->str = strdup(str);
	strtok_item->is_first_word = 1;
	strtok_item->tok = tok;
}
void free_strtok_str(strtok_str_t *item)
{
	free(item->str);
}

int
get_strtok_item(strtok_str_t *strtok_item)
{
	char *str, *str_ending;

	if (strtok_item->is_first_word == 1) {
		strtok_item->is_first_word = 0;
		if ((str = strtok(strtok_item->str, ",")) != NULL) {
			for (; str != NULL; str++) {
				if (str[0] != ' ') {
					break;
				}
			}

			str_ending = str + strlen(str) - 1;
			for (; str_ending > str; str_ending--) {
				if (str_ending[0] != ' ') {
					break;
				}
				str_ending[0] = '\0';
			}
			strtok_item->cur_str = str;
			return 1;
		}
	}else {
		if ((str = strtok(NULL, ",")) != NULL) {
			for (; str != NULL; str++) {
				if (str[0] != ' ') {
					break;
				}
			}

			str_ending = str + strlen(str) - 1;
			for (; str_ending > str; str_ending--) {
				if (str_ending[0] != ' ') {
					break;
				}
				str_ending[0] = '\0';
			}
			
			strtok_item->cur_str = str;
			return 1;
		}
	}

	return 0;
}

int check_str_contain_item(const char *str, const char *item)
{
	strtok_str_t tok;

	init_strtok_str(&tok, str, ',');
	while(get_strtok_item(&tok) == 1) {
		if (strcmp(tok.cur_str, item) == 0) {
			return 1;
		}
	}
	free_strtok_str(&tok);

	return 0;
}



int main()
{
	const char *pos = NULL;
	const char *value = NULL;
	int vlen = 0;
	char *str1 = "gzip , wzip , deflate ";
	char *str2 = "gzip";
	char *str3 = "";

	printf("main: check_str_contain_item(\"%s\", %s) return %d\n",
		str1, "wzip", check_str_contain_item(str1, "wzip"));
	printf("main: check_str_contain_item(%s, %s) return %d\n",
		str2, "wzip", check_str_contain_item(str2, "wzip"));
	printf("main: check_str_contain_item(%s, %s) return %d\n",
		str3, "wzip", check_str_contain_item(str3, "wzip"));

	
	return 0;
}













