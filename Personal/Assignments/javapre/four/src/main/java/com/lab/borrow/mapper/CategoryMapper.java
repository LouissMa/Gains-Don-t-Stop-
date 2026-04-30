package com.lab.borrow.mapper;

import com.lab.borrow.entity.Category;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface CategoryMapper {
    int insert(Category category);

    Category selectById(@Param("categoryId") Integer categoryId);

    Category selectByNameAndParent(@Param("categoryName") String categoryName, @Param("parentId") Integer parentId);

    List<Category> listAll();

    List<Category> listByParentId(@Param("parentId") Integer parentId);

    int updateById(Category category);

    int deleteById(@Param("categoryId") Integer categoryId);

    long countChildren(@Param("categoryId") Integer categoryId);
}
