class TestFact 
{
  public static long factorial(int n)
  {
    if (n == 0)
      return 1;
    else
      return (n * TestFact.factorial(n -1));
  }
  public static void main(String args[])
{
    System.out.println(TestFact.factorial(10));
  if (TestFact.factorial(10) == 3628800)
    System.out.println("Indeed 10! is 3628800");
  return;
}
}
