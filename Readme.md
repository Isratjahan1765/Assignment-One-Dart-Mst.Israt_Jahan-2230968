# 🎯 Assignment One - Dart Programming

<div align="center">

![Dart Assignment](https://img.shields.io/badge/Dart-Assignment-0175C2?style=for-the-badge&logo=dart&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-1%20to%205-FF6B6B?style=for-the-badge)

**Test Your Dart Skills! 🚀**

*From basics to advanced - prove your mastery! ⚡*

</div>

---

## 📋 Assignment Overview

This assignment tests your understanding of Dart programming concepts. The questions are designed with increasing difficulty levels (1-5).

### 🎯 Learning Objectives
- Demonstrate proficiency in Dart fundamentals
- Apply object-oriented programming concepts
- Implement advanced Dart features
- Write clean, efficient, and well-structured code

---

## 🚀 Getting Started - Step by Step Instructions

### Step 1: Fork and Clone the Repository

1. **Fork the Repository:**
   - Go to the original repository on GitHub
   - Click the "Fork" button in the top-right corner
   - This creates a copy of the repository in your GitHub account

2. **Clone Your Forked Repository:**
   ```bash
   git clone https://github.com/YOUR_USERNAME/assignment-one-dart.git
   cd assignment-one-dart
   ```

### Step 2: Create Your Own Repository

1. **Create a New Repository on GitHub:**
   - Go to GitHub.com and click the "+" icon
   - Select "New repository"
   - **Repository name:** `assignment-one-dart-YOUR_NAME-YOUR_IUB_ID` (replace YOUR_NAME with your actual name and YOUR_IUB_ID with your IUB ID)
   - Make it **Public**
   - **DO NOT** initialize with README, .gitignore, or license
   - Click "Create repository"

2. **Connect Your Local Repository to Your New GitHub Repository:**
   ```bash
   # Remove the original remote
   git remote remove origin
  
   # Add your new repository as origin
   git remote add origin https://github.com/YOUR_USERNAME/assignment-one-dart-YOUR_NAME.git
  
   # Push your code to your new repository
   git push -u origin main
   ```

### Step 3: Set Up Your Development Environment

1. **Install Dart SDK:**
   - Visit [dart.dev/get-dart](https://dart.dev/get-dart)
   - Download and install Dart SDK for your operating system
   - Verify installation: `dart --version`

2. **Install Dependencies:**
   ```bash
   dart pub get
   ```

### Step 4: Complete the Assignment

Work through each question in the `question1.dart` through `question5.dart` files. Each file contains detailed TODO comments to guide you.

### Step 5: Test Your Solutions

1. **Run All Tests:**
   For a comprehensive and easy-to-screenshot view of your progress, run:
   ```bash
   dart test test/all_tests.dart
   ```
   Or run all tests in the directory:
   ```bash
   dart test
   ```

2. **Expected Output:**
   When your implementation is correct, all tests should pass:
   ```
   All tests passed! ✅
   ```

3. **Take a Screenshot:**
   - Run `dart test test/all_tests.dart` in your terminal.
   - **IMPORTANT:** Take a high-quality screenshot showing the **entire terminal output** with all tests passing.
   - Save it as `test-results.png` in your repository root.

### Step 6: Submit Your Work

1. **Commit and Push Your Changes:**
   ```bash
   # Add all your changes
   git add .
   
   # Commit with a descriptive message
   git commit -m "Complete Dart assignment - all questions implemented"
   
   # Push to your repository
   git push origin main
   ```

2. **Submission Requirements:**
   - **GitHub Repository Link:** Share the link to your **public** GitHub repository.
   - **Test Screenshot:** Ensure `test-results.png` is visible in your repository.
   - **Public Access:** double-check that your repository is set to **Public**.

---

## 📝 Assignment Questions

Each question file (`question1.dart` to `question5.dart`) now contains an **EXPECTED OUTPUT** section at the top. Your implementation should produce output that matches this format.

---

## 🧪 Testing Your Solutions

### How to Run Tests

1. **Recommended (Unified Output):**
   ```bash
   dart test test/all_tests.dart
   ```

2. **Run Individual Tests:**
   ```bash
   dart test test/question1_test.dart
   ```

### Expected Test Results

When all tests pass, you should see a message indicating successes across all questions.

**Important:** Capture the terminal output specifically from `dart test test/all_tests.dart` for your submission screenshot.

---

## 📊 Evaluation Criteria

### Functionality (45%)
- Correct implementation of requirements.
- **Matching the Expected Output** exactly as specified in each file.
- All tests passing.

### Code Quality & Concepts (55%)
- Proper use of Dart data types, collections, and OOP principles.
- Clean, readable code with appropriate naming conventions.
- Efficient implementation of logic.

---

## 📁 Required File Structure

Your repository should have this structure:
```
assignment-one-dart-YOUR_NAME-YOUR_IUB_ID/
├── question1.dart
├── question2.dart
├── question3.dart
├── question4.dart
├── question5.dart
├── test-results.png (screenshot of passing tests)
├── README.md
├── pubspec.yaml
└── test/
    ├── all_tests.dart
    ├── question1_test.dart
    ├── question2_test.dart
    ├── question3_test.dart
    ├── question4_test.dart
    └── question5_test.dart
```

---

## 🚀 Submission Checklist

- [ ] Forked and created your own naming-compliant repository.
- [ ] Completed implementations for all 5 questions.
- [ ] Output for each question matches the **EXPECTED OUTPUT** header.
- [ ] All tests pass when running `dart test test/all_tests.dart`.
- [ ] Screenshot `test-results.png` showing all tests passing is in the root directory.
- [ ] Pushed all changes to GitHub and repository is **Public**.

---

<div align="center">

**Happy Coding! 💻**

*Show us what you've learned!*

</div>