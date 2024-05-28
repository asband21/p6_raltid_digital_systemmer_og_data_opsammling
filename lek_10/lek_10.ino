#define PKG_SIZE 10
struct state
{
	//(struct state)* my;
	int pkg_count;
	char pkg[PKG_SIZE];
	void (*next_state)(struct state *st);
};

void init(struct state *st);
void get_pkg(struct state *st);
void print_pkg(struct state *st);

void init(struct state *st)
{
	delay(10);
	//st->pkg = "123456789";
  strncpy(st->pkg, "123456789", PKG_SIZE - 1);
  st->pkg[PKG_SIZE - 1] = '\0';  // Null terminate the string
	st->next_state = get_pkg;
}

void get_pkg(struct state *st)
{
	delay(10);
	for(int i = 0;i < PKG_SIZE-1; i++)
		(st->pkg)[i] = (rand() %26) + 64 ;
	st->pkg_count = rand() % 4 + 2;
	st->next_state = (rand() % 2) ? get_pkg : print_pkg;
}

void print_pkg(struct state *st)
{
	delay(10);
	Serial.println(st->pkg);
	if(st->pkg_count > 0)
	{
		(st->pkg_count)--;
		st->next_state = print_pkg;
	}
	else
	{
		st->next_state = get_pkg;
	}	
}

void setup()
{
	Serial.begin(115200);
	struct state st = {NULL, {NULL}, init};
	while(1)
		st.next_state(&st);
}

void loop(){} 
