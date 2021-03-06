
const char conica_twflat_version[] = "$Revision: 1.3 $";
const char conica_twflat_date[]="$Date: 2003/01/30 15:45:03 $";
int  conica_twflat_main(void * d);

cmdline_spec conica_twflat_cmd[] = {
	{'o', "output", "Output file(s) base name", 1, "filename"},
    {'i', "intercepts", "Outputs y-intercept image", 0, NULL},
    {'e', "errmap", "Output error map image", 0, NULL},
    {'b', "pixmap", "Output bad pixel map", 0, NULL},
    {'p', "prop", "Proportional fit only", 0, NULL},
    {'d', "dark", "Activate dark subtraction", 1, "filename"},
    {'t', "threshold", "Change thresholds for bad pixel map", 1, "'lo hi'"},
    {'r', "rej_bord", "Rejected borders for gain norm.", 1, "'le ri bo to'"},
    {0, 0, 0, 0, 0}
};

const char conica_twflat_man[]=
"\n"
"NAME\n"
"\ttwflat -- CONICA imaging flat-field creation from twilight images.\n"
"\n"
"SYNOPSIS\n"
"\tconicap twflat [flags] [-o/--output filename] in\n"
"\n"
"DESCRIPTION\n"
"\tflat is used to process twilight data cubes to create lin�\n"
"\tear gain maps and bad pixel maps. Twilight data cubes  are\n"
"\ta  slowly increasing/decreasing signal that may be used to\n"
"\trecord pixels' responses. In this way, it is mainly possi�\n"
"\tble  to  see which pixels have a linear response, in which\n"
"\tdomain, and if the response is linear, a simple regression\n"
"\tgives  the  pixel  gain,  relative to the mean (or median)\n"
"\tgain.\n"
"\n"
"ALGORITHM\n"
"\ttwflat makes a computation of linear regression factors on\n"
"\tevery pixel, outputting the value of the fitted slope. The\n"
"\toverall luminosity in each image is  approximated  by  the\n"
"\tmedian  flux. This assumes a majority of pixels are valid,\n"
"\ta valid assumption for standard detectors.\n"
"\n"
"\tA rejection is applied on the time line  to  avoid  taking\n"
"\tinto  accounts  stellar objects which are seen in twilight\n"
"\tframes. This is done by applying a robust linear fit.\n"
"\tByproducts of this computation are the y-intercept map, an\n"
"\terror  map,  a bad pixel map. So far, the only used crite�\n"
"\trion to declare a pixel as bad is to tag all  pixels  out�\n"
"\tside a [0.5, 2.0] gain interval as invalid. Some more cri�\n"
"\tteria could be derived from a close  study  of  the  slope\n"
"\tfit.\n"
"\n"
"\tOutput  file names are all named according to a base name.\n"
"\tThe gain map is called base_flat.fits, the  intercept  map\n"
"\tis base_intercept.fits, the error map is base_errmap.fits,\n"
"\tthe bad pixel map is base_badpix.fits.  The base  name  is\n"
"\teither  given  on  the  command-line  after the input file\n"
"\tname, or it can be omitted on the  command-line.  In  that\n"
"\tcase,  the  input  file  base  name (i.e. without .FITS or\n"
"\t.fits extension) will be used.\n"
"\n"
"\tA proportional fit (y=ax) can be requested  instead  of  a\n"
"\tfull slope (y=ax+b), in which case no intercept map can be\n"
"\tproduced. The proportional fit will compute every possible\n"
"\tvalue  of  y/x,  then  take  the median one. This has been\n"
"\tfound to be quite robust.\n"
"\n"
"\tIf you provide a dark frame to  subtract  from  all  input\n"
"\ttwilight  frames,  the proportional fit mode will be acti�\n"
"\tvated automatically. Note that you can  either  provide  a\n"
"\tFITS file that will be subtracted from each input file, or\n"
"\tyou can provide an ASCII list of dark files for each input\n"
"\tfile.\n"
"\n"
"OPTIONS\n"
"\t-o or --output 'filename'\n"
"\t\tChange the output file base name. Default is 'flat':\n"
"\n"
"\t-i or --intercepts\n"
"\t\tOutput a y-intercept map. This is a byproduct of the\n"
"\t\tslope fit.\n"
"\n"
"\t-e or --errmap\n"
"\t\tOutput an error map from the linear fit. This image\n"
"\t\tcontains for each pixel the residual sum of squared\n"
"\t\terrors for all fitted points.\n"
"\n"
"\t-b or --pixmap\n"
"\t\tOutput  a bad pixel map. This is a byproduct of the\n"
"\t\tgain map. All pixels outside of a fixed [0.5,  2.0]\n"
"\t\t(inclusive) interval are tagged as bad.  The output\n"
"\t\tis a pixel map (i.e. a FITS file). If you  are  not\n"
"\t\tsatisfied with these threshold settings, use -t  or\n"
"\t\t--threshold to set other thresholds on the gain map.\n"
"\n"
"\t-p or --prop\n"
"\t\tInstead of trying to fit  a  full  slope  (y=ax+b),\n"
"\t\tonly  a  proportional  slope (y=ax) will be fitted.\n"
"\t\tThis option will be activated when dark subtraction\n"
"\t\tis requested.\n"
"\n"
"\t-d filename or --dark filename\n"
"\t\tProvide  a  dark  frame  to subtract from all input\n"
"\t\ttwilight frames or an ASCII list  of  dark  frames.\n" 
"\t\tCheck that each provided dark frame uses  the  same\n"
"\t\texposure time as the corresponding twilight  frame.\n"
"\t\tProportional fit is activated in that case.\n"
"\n"
"\t-t or --threshold 'low high'\n"
"\t\tchange the thresholding values for bad pixel map\n"
"\t\tcreation. these values are referring to normalized\n"
"\t\tflat-field values that should lie around 1.0.\n"
"\t\tall pixels in the normalized flat-field which value\n"
"\t\tlies outside of this range are flagged as bad pixels.\n"
"\t\tdefaults are 0.5 and 2.0.\n"
"\n"
"\t-r or --rej_bord 'le ri bo to'\n"
"\t\tSpecify the rejected borders (left, right, bottom, top)\n"
"\t\tfor the mean computation for gain normalization.\n"
"\n\n";

