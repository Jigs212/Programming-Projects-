<?php
session_start();
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Student</title>
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

             <!-- Student Table part-->
            <td>
            <table>
                <tr>
                    <td>
                        <div> 
                        <?php
                            // these session variables will check if an edit or delete occured and notify the user
                            if (!empty($_SESSION["check"])){
                                if ($_SESSION["check"] == true){
                                    echo "<h2>----------Record Saved!!!----------</h2>";
                                    $_SESSION["check"] = "";
                                }
                            }
                            if (!empty($_SESSION["delcheck"])){
                                if ($_SESSION["delcheck"] == true){
                                    echo "<h2>----------Record Deleted!!!----------</h2>";
                                    $_SESSION["delcheck"] = "";
                                }
                            }
                        ?>
                        <br> </div>
                    </td>
                </tr>
                <tr>
                    <td>
                        Student
                    </td>
                </tr>
                <tr>
                    <td>
                        <br>
                        <form action="" method="POST">
                            &emsp; &emsp; &emsp; &emsp;
                            <input type="text" name="searchinput">
                            <button class="button" type="submit" name="search" formaction="menu.php"> Search </button>
                            <button class="button" type="submit" formaction="addstudent.php"> Add student</button>
                        </form>
                        <br>
                        <br>
                        <!-- php mysql query table-->
                        <table>
                            <tr>
                                <th>#</th>
                                <th>Student No.</th>
                                <th>Last Name</th>
                                <th>First Name</th>
                                <th>Middle Name</th>
                                <th>Gender</th>
                                <th> &emsp; </th>
                                <th> &emsp; </th>
                            </tr>
                            <?php
                            if (isset($_POST["search"])) {
                                $search = mysqli_escape_string($con, $_POST["searchinput"]);
                                $sql = "SELECT * FROM tblstudent
                                WHERE fldstudentno = '$search' OR fldlastname = '$search' OR
                                fldfirstname = '$search' OR fldmiddlename = '$search' OR
                                fldgender = '$search';";
                                $result = mysqli_query($con,$sql);
                                $result_check = mysqli_num_rows($result);
                                if ($result_check <= 0) {                    
                                    echo "<tr><td colspan = 8>\t\t\tRecord not Found!!\t\t<td></tr>";
                                }
                                else {
                                    while ($row = mysqli_fetch_array($result)) { ?>
                                        <tr>
                                            <td> 
                                                <?php echo $row['fldindex']?>
                                            </td>
                                            <td> 
                                                <?php echo $row['fldstudentno']?>
                                            </td>
                                            <td> 
                                                <?php echo $row['fldlastname']?>
                                            </td>
                                            <td> 
                                                <?php echo $row['fldfirstname']?>
                                            </td>
                                            <td> 
                                                <?php echo $row['fldmiddlename']?>
                                            </td>
                                            <td> 
                                                <?php echo $row['fldgender']?>
                                            </td>
                                            <td>
                                                <a href="editstudent.php?s_num=<?=$row['fldstudentno']?>">Edit</a>
                                            </td>
                                            <td>
                                                <a href="deletestudent.php?s_num=<?=$row['fldstudentno']?>">Delete</a>
                                            </td>
                                        </tr>
                                        <?php
                                    }
                                }
                            }
                            else {
                                $sql = "SELECT * FROM tblstudent;";
                                $result = mysqli_query($con,$sql);
                                while ($row = mysqli_fetch_array($result)) { ?>
                                <tr>
                                    <td> 
                                        <?php echo $row['fldindex']?>
                                    </td>
                                    <td> 
                                        <?php echo $row['fldstudentno']?>
                                    </td>
                                    <td> 
                                        <?php echo $row['fldlastname']?>
                                    </td>
                                    <td> 
                                        <?php echo $row['fldfirstname']?>
                                    </td>
                                    <td> 
                                        <?php echo $row['fldmiddlename']?>
                                    </td>
                                    <td> 
                                        <?php echo $row['fldgender']?>
                                    </td>
                                    <td>
                                        <a href="editstudent.php?s_num=<?=$row['fldstudentno']?>">Edit</a>
                                    </td>
                                    <td>
                                        <a href="deletestudent.php?s_num=<?=$row['fldstudentno']?>">Delete</a>
                                    </td>
                                </tr>
                                <?php
                                }
                            }
                            ?>
                        </table>
                        <br>
                    </td>
                </tr>
                <tr>
                    <td>
                        <form action="menu.php" method="POST"> 
                        &emsp; &emsp; &emsp; &emsp;<button type="submit" name="display">Display all records</button>  
                        </form>
                    </td>
                </tr>
            </table>
            </td>
            <td></td>
        </tr>
    </table>

    <?php
    mysqli_close($con);
    ?>
</body>
</html>