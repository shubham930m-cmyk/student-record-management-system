// Student data
let students = JSON.parse(localStorage.getItem("students")) || [];


// Get grade based on marks
function getGrade(marks) {
    if (marks >= 90) {
        return "A+";
    } else if (marks >= 80) {
        return "A";
    } else if (marks >= 70) {
        return "B";
    } else if (marks >= 60) {
        return "C";
    } else if (marks >= 50) {
        return "D";
    } else if (marks >= 40) {
        return "E";
    } else {
        return "F";
    }
}


// Save students to browser storage
function saveStudents() {
    localStorage.setItem("students", JSON.stringify(students));
}


// Display students in table
function displayStudents() {

    const tableBody = document.getElementById("studentTableBody");

    tableBody.innerHTML = "";

    if (students.length === 0) {
        const row = document.createElement("tr");

        const cell = document.createElement("td");
        cell.colSpan = 6;
        cell.textContent = "No student records found.";

        row.appendChild(cell);
        tableBody.appendChild(row);

        updateStatistics();
        return;
    }

    students.forEach(function(student) {

        const row = document.createElement("tr");

        // Roll number
        const rollCell = document.createElement("td");
        rollCell.textContent = student.rollNo;

        // Name
        const nameCell = document.createElement("td");
        nameCell.textContent = student.name;

        // Branch
        const branchCell = document.createElement("td");
        branchCell.textContent = student.branch;

        // Marks
        const marksCell = document.createElement("td");
        marksCell.textContent = student.marks;

        // Grade
        const gradeCell = document.createElement("td");
        gradeCell.textContent = getGrade(student.marks);

        // Actions
        const actionCell = document.createElement("td");

        const editButton = document.createElement("button");
        editButton.textContent = "Edit";
        editButton.className = "edit-button";

        editButton.onclick = function() {
        editStudent(student.rollNo);
        };

        const deleteButton = document.createElement("button");
        deleteButton.textContent = "Delete";
        deleteButton.className = "delete-button";

        deleteButton.onclick = function() {
        deleteStudent(student.rollNo);
        };

        actionCell.appendChild(editButton);
        actionCell.appendChild(deleteButton);

        // Add cells to row
        row.appendChild(rollCell);
        row.appendChild(nameCell);
        row.appendChild(branchCell);
        row.appendChild(marksCell);
        row.appendChild(gradeCell);
        row.appendChild(actionCell);

        // Add row to table
        tableBody.appendChild(row);
    });

    updateStatistics();
}


// Add student
document.getElementById("studentForm").addEventListener("submit", function(event) {

    event.preventDefault();

    const rollNo = Number(document.getElementById("rollNo").value);
    const name = document.getElementById("name").value.trim();
    const branch = document.getElementById("branch").value.trim();
    const marks = Number(document.getElementById("marks").value);

    const message = document.getElementById("message");


    // Validate roll number
    if (rollNo <= 0) {
        message.textContent = "Roll number must be greater than 0.";
        return;
    }


    // Validate name
    if (name === "") {
        message.textContent = "Please enter student name.";
        return;
    }


    // Validate branch
    if (branch === "") {
        message.textContent = "Please enter branch.";
        return;
    }


    // Validate marks
    if (marks < 0 || marks > 100 || isNaN(marks)) {
        message.textContent = "Marks must be between 0 and 100.";
        return;
    }


    // Check duplicate roll number
    const exists = students.some(function(student) {
        return student.rollNo === rollNo;
    });

    if (exists) {
        message.textContent = "Roll number already exists.";
        return;
    }


    // Create student object
    const student = {
        rollNo: rollNo,
        name: name,
        branch: branch,
        marks: marks
    };


    // Add student
    students.push(student);

    // Save data
    saveStudents();

    // Update table
    displayStudents();


    // Success message
    message.textContent = "Student added successfully!";

    // Clear form
    document.getElementById("studentForm").reset();
});


// Search student
function searchStudent() {

    const rollNo = Number(document.getElementById("searchRoll").value);

    const result = document.getElementById("searchResult");

    if (!rollNo) {
        result.textContent = "Please enter a roll number.";
        return;
    }


    const student = students.find(function(student) {
        return student.rollNo === rollNo;
    });


    if (student) {

        result.innerHTML = `
            <strong>Student Found</strong><br>
            Roll No: ${student.rollNo}<br>
            Name: ${student.name}<br>
            Branch: ${student.branch}<br>
            Marks: ${student.marks}<br>
            Grade: ${getGrade(student.marks)}
        `;

    } else {

        result.textContent = "Student not found.";

    }
}


// Edit student
function editStudent(rollNo) {

    const student = students.find(function(student) {
        return student.rollNo === rollNo;
    });

    if (!student) {
        return;
    }


    const newName = prompt("Enter student name:", student.name);

    if (newName === null) {
        return;
    }


    const newBranch = prompt("Enter branch:", student.branch);

    if (newBranch === null) {
        return;
    }


    const newMarks = prompt("Enter marks (0-100):", student.marks);

    if (newMarks === null) {
        return;
    }


    const marks = Number(newMarks);


    if (newName.trim() === "") {
        alert("Name cannot be empty.");
        return;
    }


    if (newBranch.trim() === "") {
        alert("Branch cannot be empty.");
        return;
    }


    if (isNaN(marks) || marks < 0 || marks > 100) {
        alert("Marks must be between 0 and 100.");
        return;
    }


    student.name = newName.trim();
    student.branch = newBranch.trim();
    student.marks = marks;


    saveStudents();
    displayStudents();

    alert("Student updated successfully!");
}


// Delete student
function deleteStudent(rollNo) {

    const student = students.find(function(student) {
        return student.rollNo === rollNo;
    });

    if (!student) {
        return;
    }


    const confirmDelete = confirm(
        `Are you sure you want to delete ${student.name}?`
    );


    if (!confirmDelete) {
        return;
    }


    students = students.filter(function(student) {
        return student.rollNo !== rollNo;
    });


    saveStudents();
    displayStudents();

    alert("Student deleted successfully!");
}


// Calculate statistics
function updateStatistics() {

    const total = students.length;
    const recordCount = document.getElementById("recordCount");

    if (total === 1) {
    recordCount.textContent = "1 Student";
    } else {
    recordCount.textContent = total + " Students";
    }

    document.getElementById("totalStudents").textContent = total;


    if (total === 0) {

        document.getElementById("averageMarks").textContent = "0";
        document.getElementById("highestMarks").textContent = "0";
        document.getElementById("lowestMarks").textContent = "0";
        document.getElementById("passedStudents").textContent = "0";
        document.getElementById("failedStudents").textContent = "0";

        return;
    }


    let totalMarks = 0;
    let highest = students[0].marks;
    let lowest = students[0].marks;
    let passed = 0;
    let failed = 0;


    students.forEach(function(student) {

        totalMarks += student.marks;


        if (student.marks > highest) {
            highest = student.marks;
        }


        if (student.marks < lowest) {
            lowest = student.marks;
        }


        if (student.marks >= 40) {
            passed++;
        } else {
            failed++;
        }

    });


    const average = totalMarks / total;


    document.getElementById("averageMarks").textContent =
        average.toFixed(2);

    document.getElementById("highestMarks").textContent =
        highest;

    document.getElementById("lowestMarks").textContent =
        lowest;

    document.getElementById("passedStudents").textContent =
        passed;

    document.getElementById("failedStudents").textContent =
        failed;
}


// Load students when page opens
displayStudents();
// Sort students
function sortStudents() {

    const option = document.getElementById("sortOption").value;

    if (option === "") {
        return;
    }

    if (option === "roll") {

        students.sort(function(a, b) {
            return a.rollNo - b.rollNo;
        });

    } else if (option === "name") {

        students.sort(function(a, b) {
            return a.name.localeCompare(b.name);
        });

    } else if (option === "marks") {

        students.sort(function(a, b) {
            return b.marks - a.marks;
        });
    }

    saveStudents();
    displayStudents();
}
// Clear all students
function clearAllStudents() {

    if (students.length === 0) {
        alert("There are no student records to delete.");
        return;
    }

    const confirmClear = confirm(
        "Are you sure you want to delete ALL student records?"
    );

    if (!confirmClear) {
        return;
    }

    students = [];

    saveStudents();
    displayStudents();

    document.getElementById("sortOption").value = "";

    alert("All student records have been deleted.");
}