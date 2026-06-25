import 'package:test/test.dart';
import 'question1_test.dart' as q1;
import 'question2_test.dart' as q2;
import 'question3_test.dart' as q3;
import 'question4_test.dart' as q4;
import 'question5_test.dart' as q5;

void main() {
  group('Question 1:', q1.main);
  group('Question 2:', q2.main);
  group('Question 3:', q3.main);
  group('Question 4:', q4.main);
  group('Question 5:', q5.main);
}
