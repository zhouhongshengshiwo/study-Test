# 1. 插入数据（Insert）
向表中插入一条新记录。

INSERT INTO 表名 (列1, 列2, 列3, ...)
VALUES (值1, 值2, 值3, ...);
DiffCopyInsert
示例：

INSERT INTO students (name, age, grade)
VALUES ('张三', 18, '高三');
DiffCopyInsert
# 2. 查询数据（Select）
从表中查询数据。

SELECT 列1, 列2, ...
FROM 表名
WHERE 条件;
DiffCopyInsert
示例：

SELECT name, age
FROM students
WHERE grade = '高三';
DiffCopyInsert
# 3. 更新数据（Update）
更新表中的现有记录。

UPDATE 表名
SET 列1 = 值1, 列2 = 值2, ...
WHERE 条件;
DiffCopyInsert
示例：

UPDATE students
SET age = 19
WHERE name = '张三';
DiffCopyInsert
# 4. 删除数据（Delete）
从表中删除记录。

DELETE FROM 表名
WHERE 条件;
DiffCopyInsert
示例：

DELETE FROM students
WHERE name = '张三';
DiffCopyInsert
# 5. 删除表（Drop Table）
删除整个表。

DROP TABLE 表名;
DiffCopyInsert
示例：

DROP TABLE students;
DiffCopyInsert
# 6. 修改表结构（Alter Table）
修改现有表的结构，如添加、删除或修改列。

ALTER TABLE 表名
ADD 列名 数据类型;
DiffCopyInsert
示例：

ALTER TABLE students
ADD email VARCHAR(255);
DiffCopyInsert
# 7. 创建表（Create Table）
创建一个新表。

CREATE TABLE 表名 (
    列1 数据类型,
    列2 数据类型,
    ...
);
DiffCopyInsert
示例：

CREATE TABLE students (
    id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(50),
    age INT,
    grade VARCHAR(20)
);
DiffCopyInsert
# 8. 查询所有数据（Select All）
查询表中的所有数据。

SELECT * FROM 表名;
DiffCopyInsert
示例：

SELECT * FROM students;