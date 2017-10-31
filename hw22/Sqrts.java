import java.io.*;

class Sqrts {
  public static void main(String[] args) {
    System.out.println("sqrt(n)");
    System.out.println("--------");
    int max = Integer.parseInt(args[0]);
    int n;
    for (n=0;  n<=max;  n++)
      System.out.println(Math.sqrt(n));
    return;

  }
}