package shipmentcontainers;

/*
D    A    R    K    L      _                 _         O    R    D    D    A
    K                    / |                 | \        L    O    R         D
   A         R         _ / |                 | \ _       K    L         O    R
D         A    R    K     _ / |         _       | \ _        L    O    R    D    D
 R    K    L       _ / _   |       _ | \\    |   _ \       O    R    D    D
R         K        _ / _   |       _ | \ \   |   _ \        L    O    R
D    A    R     _ / _ / |   /     /         \ \   | \ _ \ _        K    L    O
D    D           _ / _ / |   /     /          \ \   | \ _ \ _             A
  K        _ / _ /     | /     /     _       \ \ |     \ _ \ _      L    O    R
D    A        _ / _ /      | /     /     _       \ \ |      \ _ \ _      R         K
       _ / _ /         | |     |   |   \ (O) / | |         \ _ \ _         O
D      _ / _ /          | |     |   |    \   /  | |          \ _ \ _         D
A      / _ /     |   |   | \     |   \ _   \|/   / |   |   |     \ _ \
K      / _ /      |   |   | \     |   \ _    V    / |   |   |      \ _ \         L
   / /         |   |   |   \ _ /       \ _ _ /   |   |   |         \ \
  / /          |   |   |                         |   | | |          \ \
 / /       |   | | \     \       ROWECHEN      /     / | |   |       \ \
/ /    _ _ |   | | \     \        ZHONG        /     / | |   | _ _    \ \
/ / _ /   \ | | | |   \ / \ \                 / / \ /   | | | | /   \ _ \ \
/ / _ /    \ | | | |       \ \                 / /       | | | | /    \ _ \ \
/ / /         \ \ \ \ /       /                 \       \ / / / /         \ \ \
\ / /          \ \ \ \ /       /                 \       \ / / / /          \ \ /
\|/             \|/         |         |         |           \|/             \|/
L         O     \|/         |         |   |     |           \|/        R    D
A    R    K    L             / _ |     |   | _     \      O    R    D    D    A    R
L    O         R         / _ |     |   | _     \       D    D         A    R
L    O    R    D        / / / _     | _ | | \ _   \      D    A    R         K
O    R    D              / / / _ |   | _ | | \ _   \       D    A    R    K    L
R    D    D    A    R     | / / | | / | | \ / | | \ |        K    L    O    R    D
A         R         K      | / / | | / | | \ / | | \ |              L    O         R
D    A         R         /   \ / | | | / | | / \ /     K    L         O    R
    D    D         A     /   \ / | | | / | | / \/            R    K    L    O
        R         D    D     / | / \ |   \ /        A    R    K    L    O    R
  D    A    R    K    L      / | / \ |    \/              O    R    D    D
R    K    L    O    R    D       \ /     |      D    A    R         K    L    O    R
     D    A    R             \/      |            K    L    O    R    D    D

*/
//TEMPLATE V2
import java.io.*;
import java.util.*;
import java.math.*;

public class shipmentcontainersver2 {
//Solution goes below: ------------------------------------
public void solution() throws IOException{
   int n = nextInt(), x = nextInt();
   int[][] a = new int[n][3];
   for(int i=0;i<n;i++) a[i] = new int[]{nextInt(),nextInt(),nextInt()};
   int[][] dp = new int[n][x+1];
   Arrays.sort(a, (b, c) -> Integer.compare(Math.max(b[0], b[1]), Math.max(c[0], c[1])));
   for(int i=0;i<n;i++) {
	   Arrays.fill(dp[i], -1);
	   dp[i][a[i][2]] = 1;
   }
   int res=0;
   
   for(int i=0;i<n;i++){
       int[] box = a[i];
       for(int j=0;j<i;j++) {
           if (a[j][0] < box[0] && a[j][1] < box[1])
               for (int h = 0; h < dp[i].length; h++) {
            	   if(dp[j][h] != -1 && h + box[2] < dp[i].length) {
            		    dp[i][h + box[2]] = Math.max(dp[i][h + box[2]], dp[j][h] + 1);
            	   }
               }
       }
       for(int j=0;j<=x;j++) res = Math.max(res, dp[i][j]);
   }
   
   println(res);
}

//Solution goes above: ------------------------------------
public static final String IN_FILE = "";
public static final String OUT_FILE = "";
//-------------------- ------------------------------------
//IO
public static BufferedReader br;
public static StringTokenizer st;
public static BufferedWriter bw;
public static void main(String[] args) throws IOException{
   if(IN_FILE==""){
       br = new BufferedReader(new InputStreamReader(System.in));
   }else{
       try {
           br = new BufferedReader(new FileReader(IN_FILE));
       } catch (FileNotFoundException e) {
           br = new BufferedReader(new InputStreamReader(System.in));
       }
   }
   if (OUT_FILE==""){
       bw = new BufferedWriter(new OutputStreamWriter(System.out));
   }else{
       try {
           bw = new BufferedWriter (new FileWriter(OUT_FILE) );
       } catch (FileNotFoundException e) {
           bw = new BufferedWriter(new OutputStreamWriter(System.out));
       }
   }
   (new shipmentcontainersver2()).solution();
   bw.close();//Flushes too.
}

public static String nextToken() {
   while (st == null || !st.hasMoreElements()) {
       try {
           st = new StringTokenizer(br.readLine());
       } catch (IOException e) {
           e.printStackTrace();
       }
   }
   return st.nextToken();
}

public static String nextLine() {
   st = null;
   try {
       return br.readLine();
   } catch (IOException e) {
       e.printStackTrace();
   }
   return null;
}

public static int nextInt() {
   return Integer.parseInt(nextToken());
}

public static long nextLong() {
   return Long.parseLong(nextToken());
}

public static double nextDouble() {
   return Double.parseDouble(nextToken());
}

public static void println(Object s) throws IOException{
   bw.write(s.toString()+"\n");
}

public static void println() throws IOException{
   bw.newLine();
}

public static void print(Object s) throws IOException{
   bw.write(s.toString());
}
public static void flush() throws IOException{//Useful for debug
   bw.flush();
}
//Other
public static class Arr<T> extends ArrayList<T> {} //I hate typing ArrayList
}

