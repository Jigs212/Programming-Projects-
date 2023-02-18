<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Add Student</title>
    <link rel="stylesheet" href="design.css">
</head>
<body>
    <?php
    include_once 'connect.php';
    ?>

    <table>
        <tr>
            <!-- Side menu part-->
            <td rowspan="4">
                <div class="d1"> &nbsp; <br> &nbsp; <br> &nbsp; <br> </div>
                <table>
                    <tr>
                        <td><a href="menu.php" class="link1">Student</a></td>
                    </tr>
                    <tr>
                        <td><a href="">Program</a></td>
                    </tr>
                    <tr>
                        <td><a href="">Course</a></td>
                    </tr>
                    <tr>
                        <td><a href="">Instructor</a></td>
                    </tr>
                    <tr>
                        <td><a href="">Grade</a></td>
                    </tr>
                </table>
                <div class="d1"> &nbsp; <br> &nbsp; <br> &nbsp; <br> </div>
            </td>

             <!-- Data input part-->
            <td>
            <table>
                <tr>
                    <td>
                        <div class="d1"> &nbsp; <br> &nbsp; <br> &nbsp; <br> </div>
                    </td>
                </tr>
                <tr>
                    <td>
                        Student/Add Student
                    </td>
                </tr>
                <form action="" method="POST">
                    <tr>
                        <td>
                            <div class="d1"> &nbsp; <br> &nbsp; <br> &nbsp; <br> </div>
                            
                                <table>
                                    <tr>
                                        <td>&nbsp;Student No.:&nbsp;</td>
                                        <td><input type="text" name="studentno" 
                                        value="<?php echo htmlspecialchars($_POST['studentno'] ?? '', ENT_QUOTES); ?>"></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;Last Name:&nbsp;</td>
                                        <td><input type="text" name="lastname"
                                        value="<?php echo htmlspecialchars($_POST['lastname'] ?? '', ENT_QUOTES); ?>"></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;First Name:&nbsp;</td>
                                        <td><input type="text" name="firstname"
                                        value="<?php echo htmlspecialchars($_POST['firstname'] ?? '', ENT_QUOTES); ?>"></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;Middle Name:&nbsp;</td>
                                        <td><input type="text" name="middlename"
                                        value="<?php echo htmlspecialchars($_POST['middlename'] ?? '', ENT_QUOTES); ?>"></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;Gender:&nbsp;</td>
                                        <td><input type="text" name="gender"
                                        value="<?php echo htmlspecialchars($_POST['gender'] ?? '', ENT_QUOTES); ?>"></td>
                                    </tr>
                                </table>
                                <div class="d1"> &nbsp; <br> &nbsp; <br> &nbsp; <br> </div>
                
                        </td>
                    </tr>
                    <tr>
                        <td>
                            &nbsp; &nbsp; &nbsp; &nbsp;
                            <button type="submit" name="save" formaction="addstudent.php">Save student</button> &nbsp; &nbsp;
                            <button type="submit" name="cancel" formaction="menu.php">Cancel</button>
                        </td>
                    </tr>
                </form>
            </table>
            </td>
            <td></td>
        </tr>
    </table>
    
    <?php
    if (isset($_POST["save"])) {
        $studentno = $_POST["studentno"];
        $lastname = $_POST["lastname"];
        $firstname = $_POST["firstname"];
        $middlename = $_POST["middlename"];
        $gender = $_POST["gender"];

        if (empty($studentno) || empty($lastname) || empty($firstname) || empty($middlename)
        || empty($gender)) {
            echo "!!Blank data are not allowed!! <br> Record was not saved";
        }
        else {
            $sqlsearch = "SELECT * FROM tblstudent
            WHERE fldstudentno = '$studentno';";
            $result = mysqli_query($con,$sqlsearch);
            $result_check = mysqli_num_rows($result);
            if ($result_check <= 0) {
            $sql = "INSERT INTO tblstudent (fldstudentno, fldlastname, fldfirstname,
            fldmiddlename, fldgender) 
            VALUES ('$studentno', '$lastname', '$firstname', '$middlename', '$gender');";
            mysqli_query($con, $sql);
            mysqli_close($con);
            echo "Record Saved";
            }
            else {
                echo "Duplicate student number!!! <br> Record was not saved";
            }
        }
    }
    else {
        mysqli_close($con);
    }
    ?>
</body>
</html>