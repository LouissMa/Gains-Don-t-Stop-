package com.lab.borrow.service.impl;

import com.lab.borrow.common.BizException;
import com.lab.borrow.entity.Category;
import com.lab.borrow.mapper.CategoryMapper;
import com.lab.borrow.mapper.DeviceMapper;
import com.lab.borrow.service.CategoryService;
import com.lab.borrow.util.ValidationUtils;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.util.List;

@Service
public class CategoryServiceImpl implements CategoryService {
    @Resource
    private CategoryMapper categoryMapper;

    @Resource
    private DeviceMapper deviceMapper;

    @Override
    @Transactional
    public Category create(Category category) {
        ValidationUtils.require(category != null, "分类信息不能为空");
        validateForCreate(category);

        Category existing = categoryMapper.selectByNameAndParent(category.getCategoryName(), category.getParentId());
        ValidationUtils.require(existing == null, "同一父级下分类名称不能重复");

        categoryMapper.insert(category);
        return categoryMapper.selectById(category.getCategoryId());
    }

    @Override
    @Transactional
    public Category update(Category category) {
        ValidationUtils.require(category != null, "分类信息不能为空");
        ValidationUtils.require(category.getCategoryId() != null, "分类ID不能为空");

        Category existing = categoryMapper.selectById(category.getCategoryId());
        ValidationUtils.require(existing != null, "分类不存在");

        validateForUpdate(category, existing);

        Category byName = categoryMapper.selectByNameAndParent(category.getCategoryName(), category.getParentId());
        if (byName != null && !byName.getCategoryId().equals(category.getCategoryId())) {
            throw new BizException("同一父级下分类名称不能重复");
        }

        categoryMapper.updateById(category);
        return categoryMapper.selectById(category.getCategoryId());
    }

    @Override
    @Transactional
    public void delete(Integer categoryId) {
        ValidationUtils.require(categoryId != null, "分类ID不能为空");
        Category existing = categoryMapper.selectById(categoryId);
        ValidationUtils.require(existing != null, "分类不存在");

        long childCount = categoryMapper.countChildren(categoryId);
        ValidationUtils.require(childCount == 0, "该分类存在子分类，禁止删除");

        long deviceCount = deviceMapper.countByCategoryId(categoryId);
        ValidationUtils.require(deviceCount == 0, "该分类下存在设备，禁止删除");

        categoryMapper.deleteById(categoryId);
    }

    @Override
    public Category getById(Integer categoryId) {
        ValidationUtils.require(categoryId != null, "分类ID不能为空");
        Category category = categoryMapper.selectById(categoryId);
        ValidationUtils.require(category != null, "分类不存在");
        return category;
    }

    @Override
    public List<Category> listAll() {
        return categoryMapper.listAll();
    }

    @Override
    public List<Category> listByParentId(Integer parentId) {
        return categoryMapper.listByParentId(parentId);
    }

    private void validateForCreate(Category category) {
        ValidationUtils.requireNotBlank(category.getCategoryName(), "分类名称不能为空");
        ValidationUtils.requireMaxLength(category.getCategoryName(), 50, "分类名称长度不能超过50");

        if (category.getParentId() != null) {
            Category parent = categoryMapper.selectById(category.getParentId());
            ValidationUtils.require(parent != null, "父分类不存在");
            ValidationUtils.require(parent.getParentId() == null, "不允许超过二级分类");
        }
    }

    private void validateForUpdate(Category category, Category existing) {
        ValidationUtils.requireNotBlank(category.getCategoryName(), "分类名称不能为空");
        ValidationUtils.requireMaxLength(category.getCategoryName(), 50, "分类名称长度不能超过50");

        if (category.getParentId() != null) {
            ValidationUtils.require(!category.getCategoryId().equals(category.getParentId()), "不能将分类设为自身的子分类");
            Category parent = categoryMapper.selectById(category.getParentId());
            ValidationUtils.require(parent != null, "父分类不存在");
            ValidationUtils.require(parent.getParentId() == null, "不允许超过二级分类");

            List<Category> children = categoryMapper.listByParentId(category.getCategoryId());
            for (Category child : children) {
                if (child.getCategoryId().equals(category.getParentId())) {
                    throw new BizException("不能将分类设为自身的子分类");
                }
            }
        }
    }
}
