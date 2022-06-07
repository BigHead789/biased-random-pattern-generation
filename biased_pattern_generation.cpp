#include <stdio.h>

int AND (int a, int b) {
	if(a==1 && b==1) return 1;
	else return 0;
}

int OR (int a, int b){
	if(a==0 && b==0) return 0;
	else return 1;
}

int XOR (int a, int b){
	if(a == b) return 0;
	else return 1;
}

int main(void){
	
	FILE *txt0 = fopen("myscanchain0.txt", "w");
	FILE *txt1 = fopen("myscanchain1.txt", "w");
	FILE *txt2 = fopen("myscanchain2.txt", "w");
	FILE *txt3 = fopen("myscanchain3.txt", "w");
	
	int LFSR[32];
	int feedback;
	int si[4];
	int mysc[4] = {48, 54, 40, 32};
	int t = 0;
	int basket1;
	int basket0;
	int i,j,k;
	
	char p[4][59];
	for(t=0;t<4;t++){
		p[t][57] = '\n';
		p[t][58] = '\0';
	} 
	
	for(i = 0; i<32; i++){
		if(i == 31 || i == 28) LFSR[i] = 1;
		else LFSR[i] = 0;
	}
	
	for(i = 0; i<60000; i++){
		for(j = 0; j < 57; j++){
			
			si[0] = OR(LFSR[0],OR(LFSR[1],LFSR[2]));
			si[1] = OR(LFSR[3],OR(LFSR[4],LFSR[5]));
			si[2] = OR(LFSR[31],AND(LFSR[30],OR(LFSR[29],LFSR[28])));
			si[3] = OR(LFSR[27],AND(LFSR[26],OR(LFSR[25],LFSR[24])));
			
			
			for(t=0; t<4; t++){
				if( j < mysc[t]) {
					p[t][j] = si[t] ? '1' : '0';
				}
				else p[t][j] = si[t] ? '0' : '1';	
			}
			
			feedback= XOR(XOR(LFSR[31],LFSR[27]),XOR(LFSR[26],LFSR[0]));
			basket0 = LFSR[0];
			for(k = 1; k<32; k++){
				basket1 = LFSR[k];
				LFSR[k] = basket0;
				basket0 = basket1; 
			}
			LFSR[0] = feedback;
		}
		
		fputs(p[0], txt0);
		fputs(p[1], txt1);
		fputs(p[2], txt2);
		fputs(p[3], txt3);
	}
	
	fclose(txt0);
	fclose(txt1);
	fclose(txt2);
	fclose(txt3);
	
	return 0;
}
