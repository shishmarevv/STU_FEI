import os
import subprocess
import glob
import sys


class Tester:
    def __init__(self, executable_path, stdin_dir='stdin', stdout_dir='stdout'):
        self.executable = executable_path
        self.stdin_dir = stdin_dir
        self.stdout_dir = stdout_dir
        self.passed = 0
        self.failed = 0

    def build_project(self):
        try:
            subprocess.check_call(['cmake', '--build', 'cmake-build-debug'], cwd='.')
            print("Сборка проекта успешна")
            return True
        except subprocess.CalledProcessError:
            print("Ошибка сборки проекта!")
            return False

    def run_test(self, stdin_file, stdout_file):
        try:
            with open(stdin_file, 'r') as fin, open(stdout_file, 'r') as fout:
                expected = fout.read().strip()

                # Запуск программы с аргументами из первой строки stdin
                first_line = fin.readline().strip()
                cmd = [self.executable] + first_line.split() if first_line else [self.executable]
                fin.seek(0)

                result = subprocess.run(
                    cmd,
                    stdin=fin,
                    capture_output=True,
                    text=True,
                    timeout=10
                )
                actual = result.stdout.strip()

                # Сравнение с ожидаемым выводом
                if actual == expected:
                    print(f"✅ Тест {os.path.basename(stdin_file)} пройден")
                    self.passed += 1
                else:
                    print(f"❌ Тест {os.path.basename(stdin_file)} не пройден")
                    print("Ожидаемый вывод:\n", expected)
                    print("Фактический вывод:\n", actual)
                    self.failed += 1

        except Exception as e:
            print(f"🚨 Ошибка выполнения теста: {str(e)}")
            self.failed += 1

    def run_all_tests(self):
        print("\n🔨 Запуск сборки проекта...")
        if not self.build_project():
            return

        print("\n🔍 Поиск тестов...")
        tests = glob.glob(os.path.join(self.stdin_dir, '*.txt'))

        for stdin_file in tests:
            test_name = os.path.basename(stdin_file).replace('input', 'output')
            stdout_file = os.path.join(self.stdout_dir, test_name)

            if os.path.exists(stdout_file):
                self.run_test(stdin_file, stdout_file)
            else:
                print(f"⚠️ Файл {stdout_file} не найден")

        print("\n📊 Результаты:")
        print(f"Пройдено: {self.passed}")
        print(f"Провалено: {self.failed}")
        sys.exit(self.failed > 0)


if __name__ == "__main__":
    tester = Tester(
        executable_path='./cmake-build-debug/z4',
        stdin_dir='stdin',
        stdout_dir='stdout'
    )
    tester.run_all_tests()