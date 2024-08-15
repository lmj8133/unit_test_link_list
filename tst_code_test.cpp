extern "C"
{
#include "src/link_list.h"
}
#include <gtest/gtest.h>
//#include <gmock/gmock-matchers.h>
#if 0
bool g_list;

TEST(link_list_test, TestIsTrue)
{
#if 0
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
#endif
    g_list = true;
    //EXPECT_TRUE(list_return_true());
    EXPECT_TRUE(g_list);
    g_list = true;
}

TEST(link_list_test, TestIsFalse)
{
    //EXPECT_FALSE(list_return_false());
    EXPECT_FALSE(g_list);
}
#endif
class Link_List 
{
    public:
        list_t spm_ready_list;
        uint8_t owner_src[20];
        list_node_t ext_node[SPM_TASK_NODE_TOTAL];
        void list_create(list_t *list);
        void list_node_create(list_node_t *node, void *owner_src);
    private:
        uint16_t far list_insert(list_t *list, list_node_t *new_node);
        void far list_remove_node(list_node_t *node_to_remove);
        list_node_t* far list_shift(list_t *list);

        uint16_t list_get_number_of_node(list_t *list);
        uint8_t list_get_owner_of_node(list_node_t *node);
         
        bool list_return_true(void);
        bool list_return_false(void);
};

void Link_List::list_create(list_t *list)
{
    list_init(list);
}

void Link_List::list_node_create(list_node_t *node, void *owner_src)
{
    list_init_node(node);
    node->owner = owner_src;
}

class link_list_test : public ::testing::Test
{
    public:
        void SetUp() override
        {
            link_list = new Link_List();
            link_list->list_create(&link_list->spm_ready_list);
            for(int i = 0; i < SPM_TASK_NODE_TOTAL; i++) {
                link_list->owner_src[i] = i;
                link_list->list_node_create(&link_list->ext_node[i], &link_list->owner_src[i]);
            }
        }
        void TearDown() override
        {
            delete link_list;
        }

        Link_List *link_list;
};

TEST_F(link_list_test, Initial)
{
    EXPECT_EQ(0, list_get_number_of_node(&link_list->spm_ready_list));
}

TEST_F(link_list_test, OwnerSrc)
{
    for(int i = 0; i < SPM_TASK_NODE_TOTAL; i++) {
        EXPECT_EQ(i, link_list->owner_src[i]);
    }
}


TEST_F(link_list_test, OwnerOfNodes)
{
    for(int i = 0; i < SPM_TASK_NODE_TOTAL; i++) {
        EXPECT_EQ(&link_list->owner_src[i], (link_list->ext_node[i].owner));
        EXPECT_EQ(link_list->owner_src[i], *(uint8_t *)(link_list->ext_node[i].owner));
        EXPECT_EQ(link_list->owner_src[i], list_get_owner_of_node(&link_list->ext_node[i]));
    }
}

TEST_F(link_list_test, RemoveWithoutInsert)
{
    list_remove_node(&link_list->ext_node[0]);

    EXPECT_EQ(0, list_get_number_of_node(&link_list->spm_ready_list));
}

TEST_F(link_list_test, InsertOnwNode)
{
    list_insert(&link_list->spm_ready_list, &link_list->ext_node[0]);

    EXPECT_EQ(1, list_get_number_of_node(&link_list->spm_ready_list));
    EXPECT_EQ(0, list_get_owner_of_node(link_list->spm_ready_list.end.next));
}

TEST_F(link_list_test, InsertTwoNode)
{
    list_insert(&link_list->spm_ready_list, &link_list->ext_node[0]);
    list_insert(&link_list->spm_ready_list, &link_list->ext_node[2]);

    EXPECT_EQ(2, list_get_number_of_node(&link_list->spm_ready_list));
}

TEST_F(link_list_test, InsertTwoRemoveOne)
{
    list_insert(&link_list->spm_ready_list, &link_list->ext_node[0]);
    list_insert(&link_list->spm_ready_list, &link_list->ext_node[1]);
    list_remove_node(&link_list->ext_node[0]);

    EXPECT_EQ(1, list_get_number_of_node(&link_list->spm_ready_list));
}
