/*********************************************************************/
/* vsdif   Compute local 1x1xn mean using the buffer method          */
/*********************************************************************/

#include "VisXV4.h"          /* VisionX structure include file       */
#include "Vutil.h"           /* VisionX utility header files         */

VXparam_t par[] =            /* command line structure               */
{
{    "if=",    0,   " input file vsdif: compute temporal mean"},
{    "of=",    0,   " output file "},
{    "th=",    0,   " threshold "}, 
{     0,       0,    0}
};
#define  IVAL   par[0].val
#define  OVAL   par[1].val
#define  thVAL   par[2].val

int main(argc, argv)
int argc;
char *argv[];
{
V3fstruct (im);
V3fstruct (tm);
int        x,y,z;           /* index counters                 */
int        th;   
int        n = 2;           /* Number of frames to average    */
int        sum;
     

    VXparse(&argc, &argv, par); /* parse the command line    */

    th = (thVAL ? atoi(thVAL) : 1); /* read n, default is n=1   */

    while (Vbfread( &im, IVAL, n)) {
	if ( im.type != VX_PBYTE || im.chan != 1) { /* check format  */
           fprintf (stderr, "image not byte type\n");
           exit (1);
        }
        
        for (y = im.ylo; y <= im.yhi; y++) {
           for (x = im.xlo; x <= im.xhi; x++) {
                   if(im.u[im.zhi][y][x] - im.u[im.zlo][y][x] >= th || im.u[im.zlo][y][x] - im.u[im.zhi][y][x] >= th) 
                    im.u[0][y][x] = 255;
                   else
                    im.u[0][y][x] = 128;
            }
        }
        V3fwrite (&im, OVAL); /* write the oldest frame */
    }
    exit(0);
}
