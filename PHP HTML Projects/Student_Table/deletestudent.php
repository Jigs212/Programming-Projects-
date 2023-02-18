<?php
session_start();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Delete Student</title>
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
                        <td><a href="menu.php">Student</a></td>
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

             <!-- Data view part-->
             <td>
            <?php
            if (isset($_GET["s_num"])){
                $student_no = $_GET["s_num"];$sql1 = "SELECT * FROM tblstudent
                WHERE fldstudentno = '$student_no';";
                $s_no = "";
                $lname = "";
                $fname = "";
                $mname = "";
                $gen = "";
                /*check for the related student no record*/ 
                $result = mysqli_query($con,$sql1);
                while ($row = mysqli_fetch_array($result)){
                    $s_no = $row["fldstudentno"];
                    $lname = $row["fldlastname"];
                    $fname = $row["fldfirstname"];
                    $mname = $row["fldmiddlename"];
                    $gen = $row["fldgender"]; 
                }?>
                <table>
                    <tr>
                        <td>
                            <div class="d1"> &nbsp; <br> &nbsp; <br> &nbsp; <br> </div>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            Student/Delete Student
                        </td>
                    </tr>
                    <form action="" method="POST">
                        <tr>
                            <td>
                                <div class="d1"> &nbsp; <br> &nbsp; <br> &nbsp; <br> </div>
                                <table>
                                    <tr>
                                        <td>&nbsp;Student No.:&nbsp;</td>
                                        <td><input type="text" class="in1" name="studentno" value="<?php echo htmlspecialchars($s_no)?>" readonly></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;Last Name:&nbsp;</td>
                                        <td><input type="text" class="in1" name="lastname" value="<?php echo htmlspecialchars($lname)?>" readonly></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;First Name:&nbsp;</td>
                                        <td><input type="text" class="in1" name="firstname" value="<?php echo htmlspecialchars($fname)?>" readonly></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;Middle Name:&nbsp;</td>
                                        <td><input type="text" class="in1" name="middlename" value="<?php echo htmlspecialchars($mname)?>" readonly></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;Gender:&nbsp;</td>
                                        <td><input type="text" class="in1" name="gender" value="<?php echo htmlspecialchars($gen)?>" readonly></td>
                                    </tr>
                                </table>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp; &nbsp; &nbsp; &nbsp;
                                <button type="submit" formaction="deletestudent.php" name="delete">Delete student</button> &nbsp; &nbsp;
                                <button type="submit" formaction="menu.php" name="cancel">Cancel</button>
                            </td>
                        </tr>
                    </form>
                    </table>
            <?php
             }
             ?>
            </td>
            <td></td>
        </tr>
    </table>

    <?php
    if (isset($_POST["delete"])) {
        
        $studentno = $_POST["studentno"];
        $lastname = $_POST["lastname"];
        $firstname = $_POST["firstname"];
        $middlename = $_POST["middlename"];
        $gender = $_POST["gender"];

        $sql3 = "DELETE FROM tblstudent WHERE fldstudentno = '$studentno';";
        mysqli_query($con, $sql3);
        
        $_SESSION["delcheck"] = true;
        sleep(3);
        header("Location: menu.php");
        exit(); 
    }

    mysqli_close($con);
    ?>
</body>
</html>