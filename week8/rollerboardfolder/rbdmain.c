#include "rollerboard.h"

/*This is the main*/


int main(int argc, char **argv)
{
  test();

  roller* st = ini_roll(MAXIUM);
  int move;

  /*If type only ./rollerboard (argc==1)
    just quietly run and no print out anything */

  if(argc==2)
  {
      move=move_num(argv[1],st);
      fprintf(stdout,"%d moves\n",move);
  }
  
  if(argc==3 && (strcmp(argv[1],"-v")==0))
  {
      move=move_num(argv[2],st);
      print_move(st,move);
  }
  
  if(argc==3 && (strcmp(argv[1],"-v")!=0))
  {
      print_error("Error format: ./rollerboard -v <File>");
  }

  if(argc>3)
  {
      print_error("Error format: ./rollerboard <File> || ./rollerboard -v <File>");
  }
  free(st);
  return 0;
}

/*normal test*/
void test(void)
{
    roller* r = ini_roll(LARGE);
    assert((file_open("3x3crn.rbd")));
    FILE* fp = file_open("3x3crn.rbd");
    assert(vaildline("5 4 "));
    assert(!vaildline("123455"));
    assert(vaildboard(3,3,"111000000"));
    assert(!vaildboard(3,4,"111000000"));
    assert(!vaildboard(3,3,"111100000"));
    copytoarr(&r[0],fp);
    roller h[MAX];
    char* ip1 = "000010011";
    char* ip2 = "001001010";
    for(int i=0;i<r->row;i++){
      for(int j=0;j<r->col;j++){
          h[0].arr[i][j]=ip1[i*r->col+j];
          h[1].arr[i][j]=ip2[i*r->col+j];
      }
    }
    r[1]=row_left_right(&r[0],LEFT,1);
    r[2]=col_up_down(&r[0],UP,2);
    h[2]=arrtoarr(&r[2]);
    assert(isSame(&r[1],&h[0]));
    assert(isSame(&r[2],&h[1]));
    assert(isSame(&r[2],&h[2]));
    free(r);
}
