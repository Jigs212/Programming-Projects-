<?php
session_start();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Edit Student</title>
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
                        <td><a href="menu.php" >Student</a></td>
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
            <?php
            if (isset($_GET["s_num"]) || isset($_POST["edit"])){
                if (isset($_POST["edit"])){
                    $student_no = $_SESSION['stu_num'];
                }
                else {
                    /* since the design relies on already having a value to be searched in the
                     sql, the session variables comes in handy to retain the values when
                     validation detects incorrect inputs*/
                    $student_no = $_GET["s_num"];
                    $_SESSION['stu_num'] = $_GET["s_num"];
                }
                $sql1 = "SELECT * FROM tblstudent
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
                            Student/Edit Student
                        </td>
                    </tr>
                    <form action="" method="POST">
                        <tr>
                            <td>
                                <div class="d1"> &nbsp; <br> &nbsp; <br> &nbsp; <br> </div>
                                <table>
                                    <tr>
                                        <td>&nbsp;Student No.:&nbsp;</td>
                                        <td><input type="text" name="studentno" value="<?php echo htmlspecialchars($s_no)?>">
                                        <input type="hidden" name="studentno_ref" value="<?php echo htmlspecialchars($s_no)?>"></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;Last Name:&nbsp;</td>
                                        <td><input type="text" name="lastname" value="<?php echo htmlspecialchars($lname)?>"></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;First Name:&nbsp;</td>
                                        <td><input type="text" name="firstname" value="<?php echo htmlspecialchars($fname)?>"></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;Middle Name:&nbsp;</td>
                                        <td><input type="text" name="middlename" value="<?php echo htmlspecialchars($mname)?>"></td>
                                    </tr>
                                    <tr>
                                        <td>&nbsp;Gender:&nbsp;</td>
                                        <td><input type="text" name="gender" value="<?php echo htmlspecialchars($gen)?>"></td>
                                    </tr>
                                </table>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp; &nbsp; &nbsp; &nbsp;
                                <button type="submit" formaction="editstudent.php" name="edit">Edit student</button> &nbsp; &nbsp;
                                <button type="submit" formaction="menu.php" name="cancel">Cancel</button>
                            </td>
                        </tr>
                    </form>
                    </table>
            <?php    
            }?>
            </td>
            <td></td>
        </tr>
    </table>

    <?php
    if (isset($_POST["edit"])){
        $studentno = $_POST["studentno"];
        $lastname = $_POST["lastname"];
        $firstname = $_POST["firstname"];
        $middlename = $_POST["middlename"];
        $gender = $_POST["gender"];
        $ref_studentno = $_POST["studentno_ref"];

        if (empty($studentno) || empty($lastname) || empty($firstname) || empty($middlename)
        || empty($gender)) {
            echo "!!Blank data are not allowed!! <br> Record was not saved";
        }
        else {
            $sqlsearch = "SELECT * FROM tblstudent
            WHERE fldstudentno = '$studentno';";
            $result = mysqli_query($con,$sqlsearch);
            $result_check = mysqli_num_rows($result);

            if ($result_check <= 0 || $studentno == $s_no) {
                echo "Record Saved";
                $sql2 = "UPDATE tblstudent SET fldstudentno = '$studentno', 
                fldlastname = '$lastname', fldfirstname = '$firstname', 
                fldmiddlename = '$middlename', fldgender = '$gender'
                WHERE fldstudentno = '$ref_studentno';";
        
                mysqli_query($con, $sql2);
                $_SESSION["check"] = true;

                
                sleep(3);
                header("Location: menu.php");
                exit(); 
                
            }
            else {
                echo "Duplicate student number!!! <br> Record was not saved";
            }
        }
    }
    mysqli_close($con);
    ?>
</body>
</html>