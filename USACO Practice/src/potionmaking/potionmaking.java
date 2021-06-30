//package potionmaking;

import java.io.*;
import java.util.*;
 
public class potionmaking{
	
	public static int gcd(int a, int b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
    public static void main(String[] args) throws IOException{
    	
    	//1525A
    	
        BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
        int t = Integer.parseInt(fin.readLine());
        StringBuilder fout = new StringBuilder();
        while(t-- > 0){
            int n = Integer.parseInt(fin.readLine());
            if(gcd(100, n) != 1){
                fout.append(100 / gcd(100, n)).append("\n");
            }
            else{
                fout.append("100\n");
            }
        }
        System.out.print(fout);
    }
}
