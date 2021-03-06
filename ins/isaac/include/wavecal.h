
const char isaac_wavecal_version[] = "$Revision: 1.7 $";
const char isaac_wavecal_date[]="$Date: 2002/12/11 15:40:43 $";
int  isaac_wavecal_main(void * dict);

cmdline_spec isaac_wavecal_cmd[] = {
    {'b', "border", "Declare invalid image borders", 1, "low high"},
    {'z', "zero", "Declare region to ignore on each side", 1, "left right"},
    {'T', "thermal", "Remove thermal background", 0, NULL},
    {'t', "table", "Name of spectral table to use", 1, "name"},
    {'w', "wave", "Force input wavelength range", 1, "min max"},
    {'h', "header", "Modify input file header", 0, NULL},
    {'o', "order", "Specify the order used", 1, "order"},
    {0, 0, 0, 0, 0}
};

const char isaac_wavecal_man[] =
"NAME\n"
"       wavecal - ISAAC wavelength calibration\n"
"\n"
"SYNOPSIS\n"
"       isaacp wavecal [options] in\n"
"\n"
"DESCRIPTION\n"
"       wavecal is  a  recipe  performing  an  initial  wavelength\n"
"       calibration on ISAAC spectroscopic frames.  This  tool  is\n"
"       actually giving access to the wavelength calibration tools\n"
"       available within eclipse. It is not used in itself  in the\n"
"       ISAAC pipeline  but  the  very  same  functionalities  are\n"
"       offered in spectroscopic recipes. You can use  wavecal  to\n"
"       get an initial estimate of the wavelength calibration  for\n" 
"       a given frame.\n"
"\n"
"ALGORITHM\n"
"       The recipe first collapses the input image orthogonally to\n"
"       the  spectrum  direction  to  obtain  a  1-d  signal.  The\n"
"       collapsing is resistant to noise and bad pixels  in  input\n"
"       image. In particular, image borders are often too noisy to\n"
"       be taken into account, this can be set precisely using the\n"
"       -b/--border option.\n"
"\n"
"       An initial estimate of the input wavelength range is  then\n"
"       computed using an instrument model for ISAAC. If you  have\n"
"       a better estimate for the initial  wavelength  range,  you\n"
"       can provide  it  using  the  -w/--wave  option,  providing\n"
"       wavelengths in Angstroems.\n"
"\n"
"       This range is used to locate candidate lines in a catalog.\n"
"       The used catalog can either be automatically set or forced\n"
"       to a given value  with  the  -t/--table  option.  In  this\n"
"       version the following catalogs are known to this  command:\n"
"\n"
"       auto    find automatically which table to use\n"
"       oh      use OH lines\n"
"       Xe      use Xenon table\n"
"       Ar      use Argon table\n"
"       Xe+Ar   use Xenon+Argon table\n"
"\n"
"       A 1-d cross-correlation is computed  between  the  catalog\n"
"       and the in 1-d signal. The correlation result is  required\n"
"       to be above a certain level for the recipe to declare it a\n"
"       solution.   A  number  of  issues  are  to consider before\n"
"       performing this cross-correlation:\n"
"\n"
"       If you know that some parts of the in spectrum  are  noisy\n"
"       or strong defects of the detector,  you  can  specify  the\n"
"       amount of pixels on each side of the  spectrum  to  ignore\n"
"       for correlation using the -z option. If  for  example  the\n"
"       first 128 pixels on the left  side  of  the  spectrum  are\n"
"       polluted, you would called the command  using  -z '128 0'.\n"
"       Of course, if  there  is  less  signal  to  correlate  the\n"
"       precision  of  the  solution  is  decreased   accordingly.\n"
"\n"
"       A strong perturbation in Ks  is  the  thermal  background.\n"
"       Using the -T option, you can activate  an  algorithm  that\n"
"       will try to remove  thermal  background  contributions  by\n"
"       subtracting  a  low-pass  filtered  spectrum.  This is not\n"
"       automatically  activated  by  this  recipe. The background\n"
"       removal  is  not  yet  perfect,  it  might  still  produce\n"
"       artefacts and make  the  calibration  converge  towards  a\n"
"       false solution.\n"
"\n"
"       The result of this recipe is a simple  console printout of\n"
"       the solution. No output file will be produced. If you want\n"
"       to archive the solution, you can activate the  -h/--header\n"
"       option to store the results into your image  FITS  header,\n"
"       for further refinement within e.g. IRAF.\n"
"\n"
"OPTIONS\n"
"       -b or --border 'low high'\n"
"              Declare invalid image borders for  the  collapsing.\n"
"              The borders in this case are pixels located  around\n"
"              the spectrum and parallel  to  it.  Example:  for a\n"
"              horizontal spectrum, borders  refer  to  the pixels\n"
"              above and below  the  spectrum.  Default is 80, 80.\n"
"\n"
"       -z or --zero 'left right'\n"
"              Declare parts of the spectrum  that should  not  be\n"
"              used for cross-correlation. This  time,  these  are\n"
"              pixels belonging to the collapsed spectrum.\n"
"              Default is to discard no pixel: 0,0.\n"
"\n"
"       -T or --thermal\n"
"              This flag activates thermal background subtraction.\n"
"              You will have no choice in Ks but activate  it,  if\n"
"              you want to have a reasonable solution.\n"
"\n"
"       -t or --table name\n"
"              This option forces the use of a given spectroscopic\n"
"              line table. Possible names are:\n"
"\n"
"              auto    find automatically which table to use\n"
"              oh      use OH lines\n"
"              Xe      use Xenon table\n"
"              Ar      use Argon table\n"
"              Xe+Ar   use Xenon+Argon table\n"
"\n"
"       -w or --wave 'min max'\n"
"              Declare an initial range for line  localization  in\n"
"              the spectroscopic table. Provide value in Angstroms\n"
"              Without this option, an intial estimate is computed\n"
"              using a physical model of the instrument.\n"
"\n"
"       -h or --header\n"
"              Dump the results into the appropriate  FITS  header\n"
"              keywords of the input file for  further  refinement\n"
"              with e.g. IRAF. The input file  must  be modifiable\n"
"              to do that.\n"
"\n"
"       -o or --order order\n"
"              To specify the order used.\n"
"\n"
"\n";

