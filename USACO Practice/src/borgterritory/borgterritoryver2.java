package borgterritory;

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

public class borgterritoryver2 {
//Solution goes below: ------------------------------------
public void solution() throws IOException{
   int x1 = nextInt(), y1 = nextInt(), n = nextInt();
   String s = nextLine();
   int[][] path = new int[n][2];
   int x = 0;
   int y = 0;
   for(int i=0;i<n;i++){
       char c = s.charAt(i);
       if(c=='N'){
           path[i] = new int[]{0,1};
       }
       if(c=='E'){
           path[i] = new int[]{1,0};
       }
       if(c=='S'){
           path[i] = new int[]{0,-1};
       }
       if (c == 'W') {
           path[i] = new int[]{-1,0};
       }
       x+= path[i][0];
       y += path[i][1];
       if(x==x1 && y == y1){
           println("0 0");
           return;
       }
   }
   int globalx = 0;
   int globaly = 0;
   int MAX = 100000;
   int minx = MAX;
   int miny = MAX;
   for(int i=0;i<n;i++){
//       println(String.format("CURRENT LOCATION %d %d", globalx, globaly));
       int mx = globalx+path[i][0];
       int my = globaly+path[i][1];
       int cx = globalx, cy = globaly;

       boolean dead = false;
       for(int j=i;j<n && !dead;j++){
           cx +=path[j][0];
           cy+=path[j][1];
           if(cx==mx && cy ==my && !dead){
               cx -=path[j][0];
               cy -=path[j][1];
           }
           if(cx == x1 && cy == y1){
               dead = true;
//               println("Yay");
               if(mx<minx){
                   minx = mx;
                   miny = my;
               }else if(mx == minx && my < miny){
                   minx = mx;
                   miny = my;
               }
           }
       }
       globalx = mx;
       globaly = my;
   }
   if(minx == MAX){
       println("-1");
   }else{
       println(String.format("%d %d", minx, miny));
   }
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
   (new borgterritoryver2()).solution();
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
