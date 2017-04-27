
extern void sm_init();
extern void sm_run();

int main()
{
  sm_init();

  for(;;)
    sm_run();
}
