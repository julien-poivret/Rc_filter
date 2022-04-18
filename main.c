#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	long double C;
	long double R;
	long double Fc;
        int init;
}Rc_filter_data;

/* 
     Rc filter. 1/2piRC
     two values must be provided at minimum,
     the third must be initialized with a zero...
     the data base memory is then writed with the correct  matching values.
*/

int Rc_Filter(long double R, long double C, long double Fc,Rc_filter_data* data){
	if(R==0.0 && C && Fc){
                data->R = 1/(Fc*2*M_PI*C);
                data->C = C;
                data->Fc = Fc;
                return 1;
	}	
        if(C==0.0 && R && Fc){
		data->C = 1/(Fc*2*M_PI*R);
                data->R = R;
                data->Fc = Fc;
                return 1;
	}
	if(Fc==0.0 && C && R){
		data->Fc = 1/(2*M_PI*R*C);
                data->R = R;
                data->C = C;
                return 1;
	}
		fprintf(stderr,"\33[1;1H\33[2J\33[31mError, at least 2 non null values  must be provided at minimum !\33[0m\n");
		exit(3);
	return 0;

}
	
// Data preprocessing for arguments handling.
void format_argv(char* argv[],Rc_filter_data* data){
	data->R = atof(argv[1]);
	data->C = atof(argv[2]);
	data->Fc = atof(argv[3]);
	data->init = 1;
}

int main(int argc,char* argv[]){
	// Arguments handling condition.

	char help[500]="\33[34mRc low Pass filter: \33[33m(let only the low frequency (like audio vs Radio frequence) when R is in series and C in parallel to the power supply .\n"
                       "\33[34mRc hight Pass filter: \33[33m(let only the High frequency passing ) when R is in parallel and C in series.\n"
                       "\33[34mHelp:\33[33m\n"
                       "               fast, ( 3 cli arguments forever ):  1 Resistance, 2 Capacitance, 3 Cut Off Frequency\n"
                       "             --- at least 2 arguments non Null must be provided the last third unknow is feed at 0. ---\33[0m\n"; 
	if(argc==1){
		printf("%s\n",help);
		return EXIT_SUCCESS;
	}else if(argc!=4){
		printf("3 arguments must be provided.\n");				
		return EXIT_FAILURE;
	}
        Rc_filter_data RcData = {.init=1};
        format_argv(argv,&RcData);
	Rc_Filter(RcData.R,RcData.C,RcData.Fc,&RcData);
	printf("\33[3J\33[34mRc Low Pass filters:\33[0m\n     \33[3J \33[34mFrequency \33[0mabove \33[33m%6.3Le Hz\33[0m are filtred with \33[34mR:\33[33m%6.3Le Ohm(s) \33[34mC:\33[33m%6.3Le Farad(s) \33[0m\n",RcData.Fc,RcData.R,RcData.C); 
return EXIT_SUCCESS;
}
